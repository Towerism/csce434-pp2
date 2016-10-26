#include "if_stmt.hh"

#include <ast/symbol_table.hh>
#include <codegen/codegen.hh>

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
  Assert(t != NULL && tb != NULL); // else can be NULL
  elseBody = eb;
  if (elseBody) elseBody->SetParent(this);
  exit_stmt_after_body = true;
}

void IfStmt::build_table() {
  ConditionalStmt::build_table();
  if (elseBody)
    elseBody->build_table();
}

void IfStmt::set_parent(Symbol_table& other) {
  ConditionalStmt::set_parent(other);
  if (elseBody)
    elseBody->set_parent(other);
}

void IfStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(then) ");
  if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}

void IfStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  ConditionalStmt::analyze(symbol_table, focus);
  if (elseBody) elseBody->analyze(symbol_table, focus);
}

void IfStmt::generate_extra_labels(CodeGenerator* codegen) {
  else_body_label = codegen->NewLabel();
  if (elseBody)
    false_label = else_body_label;
}

void IfStmt::generate_after_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  codegen->GenGoto(after_stmt_label);
}

void IfStmt::generate_before_stmt_end(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  if (elseBody) {
    codegen->GenLabel(else_body_label);
    elseBody->emit(codegen, frame_allocator, symbol_table);
    codegen->GenGoto(after_stmt_label);
  }
}
