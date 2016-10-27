#include "fn_decl.hh"

#include <codegen/codegen.hh>
#include <codegen/frame_allocator.hh>

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
  Assert(n != NULL && r!= NULL && d != NULL);
  (returnType=r)->SetParent(this);
  (formals=d)->SetParentAll(this);
  body = NULL;
  symbol_table.set_return_type(returnType);
  formals_table.set_parent(symbol_table);
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

void FnDecl::set_parent(Symbol_table& other) {
  symbol_table.set_parent(other);
}

void FnDecl::build_table() {
  formals->Apply([&](VarDecl* decl) { formals_table.declare(decl); });
  if (body) {
    body->build_table();
    body->set_parent(formals_table);
  }
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

void FnDecl::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  codegen->GenFnLabel(id->getName().c_str());
  auto function = codegen->GenBeginFunc();
  auto body_allocator = new Frame_allocator(fpRelative, Frame_growth::Downwards);
  body->emit(codegen, body_allocator, &this->symbol_table);
  function->SetFrameSize(body_allocator->size());
  codegen->GenEndFunc();
}
