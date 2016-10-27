#include "for_stmt.hh"

#include <codegen/codegen.hh>

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) {
  Assert(i != NULL && t != NULL && s != NULL && b != NULL);
  (init=i)->SetParent(this);
  (step=s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) {
  init->Print(indentLevel+1, "(init) ");
  test->Print(indentLevel+1, "(test) ");
  step->Print(indentLevel+1, "(step) ");
  body->Print(indentLevel+1, "(body) ");
}

void ForStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  ConditionalStmt::analyze(symbol_table, focus);
  init->analyze(symbol_table, focus);
  step->analyze(symbol_table, focus);
}

void ForStmt::generate_before_begin_label(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  init->emit(codegen, frame_allocator, symbol_table);
}

void ForStmt::generate_after_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  step->emit(codegen, frame_allocator, symbol_table);
  codegen->GenGoto(before_stmt_label);
}
