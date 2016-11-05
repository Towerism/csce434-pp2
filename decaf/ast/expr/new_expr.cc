#include "new_expr.hh"

#include <util/utility.hh>

#include <ast/decl/class_decl.hh>
#include <ast/identifier.hh>
#include <ast/stmt/program.hh>

#include <codegen/codegen.hh>
#include <codegen/label_transformer.hh>
NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType = c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) { cType->Print(indentLevel + 1); }

void NewExpr::analyze(Symbol_table *symbol_table, reasonT focus) {
  cType->verify(LookingForClass);
}

void NewExpr::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                   Symbol_table *symbol_table) {
  auto class_decl = Program::symbol_table.get_class(cType->getName());
  auto instance_size = class_decl->get_size();
  auto size = codegen->GenLoadConstant(instance_size, frame_allocator);
  frame_location = codegen->GenBuiltInCall(Alloc, frame_allocator, size);
  auto vtable = codegen->GenLoadLabel(
      Label_transformer::get_for_class(class_decl->getName()).c_str(),
      frame_allocator);
  codegen->GenStore(frame_location, vtable);
}
