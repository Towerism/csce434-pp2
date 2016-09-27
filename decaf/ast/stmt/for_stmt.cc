#include "for_stmt.hh"

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) {
  Assert(i != NULL && t != NULL && s != NULL && b != NULL);
  (init=i)->SetParent(this);
  (step=s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) {
  init->Print(indentLevel+1, "(init) ");
  test->Print(indentLevel+1, "(test) ");
  step->Print(indentLevel+1, "(step) ");
  body->Print(indentLevel+1, "(body) ");
}
