#include "return_stmt.hh"

#include <util/utility.hh>

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) {
  Assert(e != NULL);
  (expr=e)->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) {
  expr->Print(indentLevel+1);
}
