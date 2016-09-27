#include "if_stmt.hh"

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
  Assert(t != NULL && tb != NULL); // else can be NULL
  elseBody = eb;
  if (elseBody) elseBody->SetParent(this);
}

void IfStmt::build_table() {
  ConditionalStmt::build_table();
  if (elseBody) elseBody->build_table();
}

void IfStmt::analyze(reasonT focus) {
  ConditionalStmt::analyze(focus);
  if (elseBody) elseBody->analyze(focus);
}

void IfStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(then) ");
  if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}
