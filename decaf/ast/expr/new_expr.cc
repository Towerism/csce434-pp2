#include "new_expr.hh"

#include <util/utility.hh>

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) {
  cType->Print(indentLevel+1);
}
