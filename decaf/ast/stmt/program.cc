#include "program.hh"

Symbol_table Program::symbol_table;

Program::Program(List<Decl*> *d) {
  Assert(d != NULL);
  (decls=d)->SetParentAll(this);
}

void Program::PrintChildren(int indentLevel) {
  decls->PrintAll(indentLevel+1);
  printf("\n");
}

void Program::build_table() {
  decls->Apply([&](Decl* decl) { Program::symbol_table.declare(decl); });
  decls->Apply([&](Decl* decl) {
      decl->build_table();
      decl->set_parent(Program::symbol_table);
    });
}

void Program::analyze(reasonT focus) {
  build_table();

  decls->Apply([&](Decl* decl) { decl->analyze(focus); });
}
