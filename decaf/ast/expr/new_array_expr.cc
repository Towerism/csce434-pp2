#include "new_array_expr.hh"

#include <util/utility.hh>

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
  Assert(sz != NULL && et != NULL);
  (size=sz)->SetParent(this);
  (elemType=et)->SetParent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) {
  size->Print(indentLevel+1);
  elemType->Print(indentLevel+1);
}
