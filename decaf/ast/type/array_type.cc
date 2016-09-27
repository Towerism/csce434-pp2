#include "array_type.hh"

#include <util/utility.hh>

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
  Assert(et != NULL);
  (elemType=et)->SetParent(this);
}
void ArrayType::PrintChildren(int indentLevel) {
  elemType->Print(indentLevel+1);
}

void ArrayType::analyze(reasonT focus) {
  elemType->analyze(focus);
}
