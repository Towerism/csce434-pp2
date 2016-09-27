/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.hh"

#include <algorithm>

#include <util/errors.hh>
#include "ast_type.hh"
#include "ast_stmt.hh"


Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
  Assert(n != NULL);
  (id=n)->SetParent(this);
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
  Assert(n != NULL && t != NULL);
  (type=t)->SetParent(this);
}

void VarDecl::PrintChildren(int indentLevel) {
  type->Print(indentLevel+1);
  id->Print(indentLevel+1);
}

void VarDecl::analyze(reasonT focus) {
  type->analyze(focus);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
  // extends can be NULL, impl & mem may be empty lists but cannot be NULL
  Assert(n != NULL && imp != NULL && m != NULL);
  extends = ex;
  if (extends) extends->SetParent(this);
  (implements=imp)->SetParentAll(this);
  (members=m)->SetParentAll(this);
}

void ClassDecl::PrintChildren(int indentLevel) {
  id->Print(indentLevel+1);
  if (extends) extends->Print(indentLevel+1, "(extends) ");
  implements->PrintAll(indentLevel+1, "(implements) ");
  members->PrintAll(indentLevel+1);
}

void ClassDecl::build_table() {
  members->Apply([&](Decl* decl) { symbol_table.declare(decl); });
  members->Apply([&](Decl* decl) { decl->build_table(); });
}

void ClassDecl::analyze(reasonT focus) {
  if (extends) {
    extends->analyze(LookingForClass);
    auto superClass = Program::symbol_table.get_class(extends->getName());
    if (superClass)
      symbol_table.set_super(superClass->symbol_table);
  }
  implements->Apply([&](NamedType* type) { type->analyze(LookingForInterface); });
  implements->Apply([&](NamedType* type) {
      auto interface = Program::symbol_table.get_interface(type->getName());
      if (interface) {
        auto members = interface->get_members();
        members->Apply([&](Decl* member) {
          symbol_table.add_virtual(member);
          });
      }
    });
  members->Apply([&](Decl* decl) {
      symbol_table.check_super(decl);
    });
  members->Apply([&](Decl* decl) {
      symbol_table.check_virtual(decl);
    });
  members->Apply([&](Decl* decl) { decl->analyze(LookingForType); });
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
  Assert(n != NULL && m != NULL);
  (members=m)->SetParentAll(this);
}

void InterfaceDecl::PrintChildren(int indentLevel) {
  id->Print(indentLevel+1);
  members->PrintAll(indentLevel+1);
}

void InterfaceDecl::analyze(reasonT focus) {
}

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
