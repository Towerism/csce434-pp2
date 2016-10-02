#include "if_stmt.hh"

#include <ast/symbol_table.hh>

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
  Assert(t != NULL && tb != NULL); // else can be NULL
  elseBody = eb;
  if (elseBody) elseBody->SetParent(this);
}

void IfStmt::build_table() {
  ConditionalStmt::build_table();
  if (elseBody) elseBody->build_table();
}

void IfStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(then) ");
  if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}

void IfStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  ConditionalStmt::analyze(symbol_table, focus);
  if (elseBody) elseBody->analyze(symbol_table, focus);
}
