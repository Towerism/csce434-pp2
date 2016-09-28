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

void CaseStmt::analyze(reasonT focus) {
  body->Apply([&](Stmt* stmt) { stmt->analyze(focus); });
}

void CaseStmt::build_table() {
  body->Apply([&](Stmt* stmt) { stmt->build_table(); });
}