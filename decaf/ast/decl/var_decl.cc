#include "var_decl.hh"

#include <codegen/codegen.hh>
#include <codegen/frame_allocator.hh>
#include <util/utility.hh>

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
  Assert(n != NULL && t != NULL);
  (type=t)->SetParent(this);
}

void VarDecl::PrintChildren(int indentLevel) {
  type->Print(indentLevel+1);
  id->Print(indentLevel+1);
}

void VarDecl::analyze(reasonT focus) {
  type->analyze(focus);
}

void VarDecl::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  frame_location = frame_allocator->allocate(4, strdup(id->getName().c_str()));
}
