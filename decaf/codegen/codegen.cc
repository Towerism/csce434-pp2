/* File: codegen.cc
 * ----------------
 * Implementation for the CodeGenerator class. The methods don't do anything
 * too fancy, mostly just create objects of the various Tac instruction
 * classes and append them to the list.
 */

#include "codegen.hh"

#include <string.h>

#include "complex_op_factory.hh"
#include "frame_allocator.hh"
#include "label_transformer.hh"
#include "linker.hh"

#include <arch/mips/mips.hh>
#include <arch/tac.hh>

Location* CodeGenerator::ThisPtr= new Location(fpRelative, 4, "this");

CodeGenerator::CodeGenerator()
{
}

char *CodeGenerator::NewLabel()
{
  static int nextLabelNum = 0;
  char temp[10];
  sprintf(temp, "_L%d", nextLabelNum++);
  return strdup(temp);
}


Location *CodeGenerator::GenTempVar(Frame_allocator* frame_allocator)
{
  static int nextTempNum;
  char temp[10];
  Location *result = NULL;
  sprintf(temp, "_tmp%d", nextTempNum++);
  result = frame_allocator->allocate(VarSize, temp);
  Assert(result != NULL);
  return result;
}


Location *CodeGenerator::GenLoadConstant(int value, Frame_allocator* frame_allocator)
{
  Location *result = GenTempVar(frame_allocator);
  code.push_back(new LoadConstant(result, value));
  return result;
}

Location *CodeGenerator::GenLoadConstant(const char *s, Frame_allocator* frame_allocator)
{
  Location *result = GenTempVar(frame_allocator);
  code.push_back(new LoadStringConstant(result, s));
  return result;
}

Location *CodeGenerator::GenLoadLabel(const char *label, Frame_allocator* frame_allocator)
{
  Location *result = GenTempVar(frame_allocator);
  code.push_back(new LoadLabel(result, label));
  return result;
}


void CodeGenerator::GenAssign(Location *dst, Location *src)
{
  code.push_back(new Assign(dst, src));
}


Location *CodeGenerator::GenLoad(Location *ref, Frame_allocator* frame_allocator, int offset)
{
  Location *result = GenTempVar(frame_allocator);
  code.push_back(new Load(result, ref, offset));
  return result;
}

void CodeGenerator::GenStore(Location *dst,Location *src, int offset)
{
  code.push_back(new Store(dst, src, offset));
}


Location *CodeGenerator::GenBinaryOp(const char *opName, Location *op1,
                                     Location *op2, Frame_allocator* frame_allocator)
{
  auto op_code = BinaryOp::OpCodeForName(opName);
  return GenBinaryOp(op_code, op1, op2, frame_allocator);
}
Location *CodeGenerator::GenBinaryOp(BinaryOp::OpCode op, Location *op1,
                                     Location *op2, Frame_allocator* frame_allocator)
{
  Location *result = GenTempVar(frame_allocator);
  code.push_back(new BinaryOp(op, result, op1, op2));
  return result;
}

Location *CodeGenerator::GenNot(Location *src, Frame_allocator* frame_allocator) {
  Location * result = GenTempVar(frame_allocator);
  code.push_back(new Not(result, src));
  return result;
}

Location *CodeGenerator::GenComplexBinaryOp(const char *opName, Location *op1,
                                     Location *op2, Frame_allocator* frame_allocator)
{
  Complex_op_factory complex_op_factory(this, frame_allocator);
  return complex_op_factory.make_complex_op(opName, op1, op2);
}

#include <iostream>
void CodeGenerator::GenFnLabel(const char *label) {
  std::string transformed_label;
  if (Linker::check_label_for_main_linkage(label))
    transformed_label = std::string(label);
  else
    transformed_label = Label_transformer::get_for_function(label);
  GenLabel(transformed_label.c_str());
}

void CodeGenerator::GenLabel(const char *label)
{
  code.push_back(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, const char *label)
{
  code.push_back(new IfZ(test, label));
}

void CodeGenerator::GenGoto(const char *label)
{
  code.push_back(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val)
{
  code.push_back(new Return(val));
}


BeginFunc *CodeGenerator::GenBeginFunc()
{
  BeginFunc *result = new BeginFunc;
  code.push_back(result);
  return result;
}

void CodeGenerator::GenEndFunc()
{
  code.push_back(new EndFunc());
}

void CodeGenerator::GenPushParam(Location *param)
{
  code.push_back(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams)
{
  Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0); // sanity check
  if (numBytesOfParams > 0)
    code.push_back(new PopParams(numBytesOfParams));
}

Location *CodeGenerator::GenLCall(const char *label, bool fnHasReturnValue, Frame_allocator* frame_allocator)
{
  Location *result = fnHasReturnValue ? GenTempVar(frame_allocator) : NULL;
  auto transformed_label = Label_transformer::get_for_function(label).c_str();
  code.push_back(new LCall(transformed_label, result));
  return result;
}

Location *CodeGenerator::GenACall(Location *fnAddr, bool fnHasReturnValue, Frame_allocator* frame_allocator)
{
  Location *result = fnHasReturnValue ? GenTempVar(frame_allocator) : NULL;
  code.push_back(new ACall(fnAddr, result));
  return result;
}


static struct _builtin {
  const char *label;
  int numArgs;
  bool hasReturn;
} builtins[] =
  {{"_Alloc", 1, true},
   {"_ReadLine", 0, true},
   {"_ReadInteger", 0, true},
   {"_StringEqual", 2, true},
   {"_PrintInt", 1, false},
   {"_PrintString", 1, false},
   {"_PrintBool", 1, false},
   {"_Halt", 0, false}};

Location *CodeGenerator::GenBuiltInCall(BuiltIn bn, Frame_allocator* frame_allocator, Location *arg1, Location *arg2)
{
  Assert(bn >= 0 && bn < NumBuiltIns);
  struct _builtin *b = &builtins[bn];
  Location *result = NULL;

  if (b->hasReturn) result = GenTempVar(frame_allocator);
  // verify appropriate number of non-NULL arguments given
  Assert((b->numArgs == 0 && !arg1 && !arg2)
         || (b->numArgs == 1 && arg1 && !arg2)
         || (b->numArgs == 2 && arg1 && arg2));
  if (arg2) code.push_back(new PushParam(arg2));
  if (arg1) code.push_back(new PushParam(arg1));
  code.push_back(new LCall(b->label, result));
  GenPopParams(VarSize*b->numArgs);
  return result;
}


void CodeGenerator::GenVTable(const char *className, List<const char *> *methodLabels)
{
  code.push_back(new VTable(className, methodLabels));
}


void CodeGenerator::DoFinalCodeGen()
{
  if (IsDebugOn("tac")) { // if debug don't translate to mips, just print Tac
    std::list<Instruction*>::iterator p;
    for (p= code.begin(); p != code.end(); ++p) {
      (*p)->Print();
    }
  }  else {
    Mips mips;
    mips.EmitPreamble();

    std::list<Instruction*>::iterator p;
    for (p= code.begin(); p != code.end(); ++p) {
      (*p)->Emit(&mips);
    }
  }
}


