#include "class_decl.hh"

#include <ast/decl/ast_decl.hh>

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
  add_virtuals();
  members->Apply([&](Decl* decl) { symbol_table.check_virtual(decl); });
}

void ClassDecl::add_virtuals() {
  implements->Apply([&](NamedType* type) {
      auto interface = Program::symbol_table.get_interface(type->getName());
      if (interface) {
        auto members = interface->get_members();
        members->Apply([&](Decl* member) {
            symbol_table.add_virtual(type, dynamic_cast<FnDecl*>(member));
          });
      }
    });
}

void ClassDecl::analyze(reasonT focus) {
  extend();
  members->Apply([&](Decl* decl) { symbol_table.check_super(decl); });
  implements->Apply([&](NamedType* type) { type->analyze(LookingForInterface); });
  members->Apply([&](Decl* decl) { decl->analyze(LookingForType); });
  symbol_table.check_virtuals_implemented(this, implements);
}

void ClassDecl::extend() {
  if (extends) {
    extends->analyze(LookingForClass);
    auto superClass = Program::symbol_table.get_class(extends->getName());
    if (superClass)
      symbol_table.set_super(superClass->symbol_table);
  }
}
