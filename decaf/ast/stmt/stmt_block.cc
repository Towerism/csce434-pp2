#include "stmt_block.hh"

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
  Assert(d != NULL && s != NULL);
  (decls=d)->SetParentAll(this);
  (stmts=s)->SetParentAll(this);
}

void StmtBlock::PrintChildren(int indentLevel) {
  decls->PrintAll(indentLevel+1);
  stmts->PrintAll(indentLevel+1);
}

void StmtBlock::build_table() {
  decls->Apply([&](Decl* decl) { symbol_table.declare(decl); });
  decls->Apply([&](Decl* decl) { decl->build_table(); });
  stmts->Apply([&](Stmt* stmt) { stmt->build_table();
      stmt->set_parent(symbol_table);
    });
}

void StmtBlock::set_parent(Symbol_table& other) {
  symbol_table.set_parent(other);
}

void StmtBlock::analyze(reasonT focus) {
  decls->Apply([&](VarDecl* decl) { decl->analyze(focus); });
  stmts->Apply([&](Stmt* stmt) { stmt->analyze(&symbol_table, focus); });
}

void StmtBlock::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  decls->Apply([&](Decl* decl) { decl->emit(codegen, frame_allocator, &this->symbol_table); });
  stmts->Apply([&](Stmt* stmt) { stmt->emit(codegen, frame_allocator, &this->symbol_table); });
}
