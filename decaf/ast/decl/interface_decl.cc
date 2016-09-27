#include "interface_decl.hh"

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
  Assert(n != NULL && m != NULL);
  (members=m)->SetParentAll(this);
}

void InterfaceDecl::PrintChildren(int indentLevel) {
  id->Print(indentLevel+1);
  members->PrintAll(indentLevel+1);
}

void InterfaceDecl::build_table() {
  members->Apply([&](Decl* decl) { symbol_table.declare(decl); });
}
