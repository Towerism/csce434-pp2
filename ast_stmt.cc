/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.hh"
#include "ast_type.hh"
#include "ast_decl.hh"
#include "ast_expr.hh"

Symbol_table Program::symbol_table;

Program::Program(List<Decl*> *d) {
  Assert(d != NULL);
  (decls=d)->SetParentAll(this);
}

void Program::PrintChildren(int indentLevel) {
  decls->PrintAll(indentLevel+1);
  printf("\n");
}

void Program::analyze(Scope_stack& scope_stack) {
  for (int i = 0; i < decls->NumElements(); ++i) {
    Program::symbol_table.declare(decls->Nth(i));
  }

  for (int i = 0; i < decls->NumElements(); ++i) {
    auto d = decls->Nth(i);
    d->analyze(scope_stack);
  }
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
  Assert(d != NULL && s != NULL);
  (decls=d)->SetParentAll(this);
  (stmts=s)->SetParentAll(this);
}

void StmtBlock::PrintChildren(int indentLevel) {
  decls->PrintAll(indentLevel+1);
  stmts->PrintAll(indentLevel+1);
}

void StmtBlock::analyze(Scope_stack& scope_stack) {
  decls->Apply([&](VarDecl* decl) { decl->analyze(scope_stack); });
  stmts->Apply([&](Stmt* stmt) { stmt->analyze(scope_stack); });
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {    Assert(t != NULL && b != NULL);
  (test=t)->SetParent(this);    (body=b)->SetParent(this);
}

void ConditionalStmt::analyze(Scope_stack& scope_stack) {
  body->analyze(scope_stack);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) {    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
  (init=i)->SetParent(this);
  (step=s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) {
  init->Print(indentLevel+1, "(init) ");
  test->Print(indentLevel+1, "(test) ");
  step->Print(indentLevel+1, "(step) ");
  body->Print(indentLevel+1, "(body) ");
}

void WhileStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(body) ");
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {    Assert(t != NULL && tb != NULL); // else can be NULL
  elseBody = eb;
  if (elseBody) elseBody->SetParent(this);
}

void IfStmt::analyze(Scope_stack& scope_stack) {
  ConditionalStmt::analyze(scope_stack);
  if (elseBody) elseBody->analyze(scope_stack);
}

void IfStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(then) ");
  if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}

CaseStmt::CaseStmt(yyltype loc, IntConstant* label, List<Stmt*>* body)
  : Stmt(loc), label(label), body(body) {
  this->label->SetParent(this);
  this->body->SetParentAll(this);
}

void CaseStmt::PrintChildren(int identLevel) {
  this->label->Print(identLevel+1, "(label) ");
  this->body->PrintAll(identLevel+1);
}

DefaultStmt::DefaultStmt(yyltype loc, List<Stmt*>* body) : Stmt(loc), body(body) {
  this->body->SetParentAll(this);
}

void DefaultStmt::PrintChildren(int identLevel) {
  this->body->PrintAll(identLevel+1);
}

SwitchStmt::SwitchStmt(yyltype loc, Expr* test, List<CaseStmt*>* cases, DefaultStmt* defaultStmt)
  : Stmt(loc), test(test), cases(cases), defaultStmt(defaultStmt) {
  this->test->SetParent(this);
  this->cases->SetParentAll(this);
  this->defaultStmt->SetParent(this);
}

void SwitchStmt::PrintChildren(int identLevel) {
  this->test->Print(identLevel+1, "(test) ");
  this->cases->PrintAll(identLevel+1, NULL);
  this->defaultStmt->Print(identLevel+1, "(default) ");
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) {    Assert(e != NULL);
  (expr=e)->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) {
  expr->Print(indentLevel+1);
}
PrintStmt::PrintStmt(List<Expr*> *a) {    Assert(a != NULL);
  (args=a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indentLevel) {
  args->PrintAll(indentLevel+1, "(args) ");
}


