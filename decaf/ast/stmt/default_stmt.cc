#include "default_stmt.hh"

DefaultStmt::DefaultStmt(yyltype loc, List<Stmt*>* body) : Stmt(loc), body(body) {
  this->body->SetParentAll(this);
}

void DefaultStmt::PrintChildren(int identLevel) {
  this->body->PrintAll(identLevel+1);
}

void DefaultStmt::analyze(reasonT focus) {
  body->Apply([&](Stmt* stmt) { stmt->analyze(focus); });
}

void DefaultStmt::build_table() {
  body->Apply([&](Stmt* stmt) { stmt->build_table(); });
}
