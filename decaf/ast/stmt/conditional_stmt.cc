#include "conditional_stmt.hh"

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
  Assert(t != NULL && b != NULL);
  (test=t)->SetParent(this);    (body=b)->SetParent(this);
}

void ConditionalStmt::build_table() {
  body->build_table();
}

void ConditionalStmt::analyze(reasonT focus) {
  body->analyze(focus);
}
