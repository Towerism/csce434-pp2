#include "fn_decl.hh"

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
  Assert(n != NULL && r!= NULL && d != NULL);
  (returnType=r)->SetParent(this);
  (formals=d)->SetParentAll(this);
  body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) {
  (body=b)->SetParent(this);
}

void FnDecl::PrintChildren(int indentLevel) {
  returnType->Print(indentLevel+1, "(return type) ");
  id->Print(indentLevel+1);
  formals->PrintAll(indentLevel+1, "(formals) ");
  if (body) body->Print(indentLevel+1, "(body) ");
}

void FnDecl::build_table() {
  formals->Apply([&](VarDecl* decl) { symbol_table.declare(decl); });
  if (body)
    body->build_table();
}

void FnDecl::analyze(reasonT focus) {
  formals->Apply([&](VarDecl* decl) { decl->analyze(focus); });
  if (body)
    body->analyze(focus);
}

bool FnDecl::matches_signature(FnDecl* other) {
  if (formals->NumElements() != other->formals->NumElements())
    return false;
  return returnType->equal(other->returnType) &&
    std::equal(formals->begin(), formals->end(), other->formals->begin(),
                    [](VarDecl* a, VarDecl* b) {
                      return a->getType()->equal(b->getType());
                    });
}