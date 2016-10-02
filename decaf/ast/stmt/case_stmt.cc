#include "case_stmt.hh"

CaseStmt::CaseStmt(yyltype loc, IntConstant* label, List<Stmt*>* body)
  : Stmt(loc), label(label), body(body) {
  this->label->SetParent(this);
  this->body->SetParentAll(this);
}

void CaseStmt::PrintChildren(int identLevel) {
  this->label->Print(identLevel+1, "(label) ");
  this->body->PrintAll(identLevel+1);
}

void CaseStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  body->Apply([&](Stmt* stmt) { stmt->analyze(symbol_table, focus); });
}

void CaseStmt::build_table() {
  body->Apply([&](Stmt* stmt) { stmt->build_table(); });
}

void CaseStmt::set_parent(Symbol_table& other) {
  body->Apply([&](Stmt* stmt) { stmt->set_parent(other); });
}
