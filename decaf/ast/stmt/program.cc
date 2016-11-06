#include "program.hh"

#include <ast/decl/class_decl.hh>

#include <codegen/codegen.hh>
#include <codegen/frame_allocator.hh>
#include <codegen/linker.hh>

Symbol_table Program::symbol_table;

Program::Program(List<Decl *> *d) {
  Assert(d != NULL);
  (decls = d)->SetParentAll(this);
}

void Program::PrintChildren(int indentLevel) {
  decls->PrintAll(indentLevel + 1);
  printf("\n");
}

void Program::build_table() {
  decls->Apply([&](Decl *decl) { Program::symbol_table.declare(decl); });
  decls->Apply([&](Decl *decl) {
    decl->build_table();
    decl->set_parent(Program::symbol_table);
  });
}

void Program::analyze(reasonT focus) {
  build_table();

  decls->Apply([&](Decl *decl) { decl->analyze(focus); });
}

void Program::emit() {
  auto codegen = new CodeGenerator();
  auto frame_allocator = new Frame_allocator(gpRelative, Frame_growth::Upwards);
  decls->Apply([&](Decl *decl) {
    auto class_decl = dynamic_cast<ClassDecl *>(decl);
    if (class_decl)
      class_decl->prepare_for_emission(codegen, &symbol_table);
  });
  decls->Apply(
      [&](Decl *decl) { decl->emit(codegen, frame_allocator, &symbol_table); });
  if (Linker::link())
    codegen->DoFinalCodeGen();
}
