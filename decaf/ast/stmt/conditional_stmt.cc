#include "conditional_stmt.hh"

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
  Assert(t != NULL && b != NULL);
  (test=t)->SetParent(this);    (body=b)->SetParent(this);
}

void ConditionalStmt::build_table() {
  body->build_table();
}

void ConditionalStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  body->analyze(symbol_table, focus);
  test->analyze(symbol_table, focus);
}
