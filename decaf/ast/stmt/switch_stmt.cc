#include "switch_stmt.hh"

SwitchStmt::SwitchStmt(yyltype loc, Expr* test, List<CaseStmt*>* cases, DefaultStmt* defaultStmt)
  : Stmt(loc), test(test), cases(cases), defaultStmt(defaultStmt) {
  this->test->SetParent(this);
  this->cases->SetParentAll(this);
  if (defaultStmt)
    this->defaultStmt->SetParent(this);
}

void SwitchStmt::PrintChildren(int identLevel) {
  this->test->Print(identLevel+1, "(test) ");
  this->cases->PrintAll(identLevel+1, NULL);
  this->defaultStmt->Print(identLevel+1, "(default) ");
}

void SwitchStmt::build_table() {
  cases->Apply([&](CaseStmt* caseStmt) { caseStmt->build_table(); });
  if (defaultStmt)
    defaultStmt->build_table();
}

void SwitchStmt::analyze(reasonT focus) {
  cases->Apply([&](CaseStmt* caseStmt) { caseStmt->analyze(focus); });
  if (defaultStmt)
    defaultStmt->analyze(focus);
}
