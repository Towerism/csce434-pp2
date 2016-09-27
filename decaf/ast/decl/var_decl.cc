#include "var_decl.hh"

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
