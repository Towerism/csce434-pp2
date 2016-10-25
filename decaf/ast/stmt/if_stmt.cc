#include "if_stmt.hh"

#include <ast/symbol_table.hh>
#include <codegen/codegen.hh>

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
  Assert(t != NULL && tb != NULL); // else can be NULL
  elseBody = eb;
  if (elseBody) elseBody->SetParent(this);
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

void IfStmt::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  generate_labels(codegen);
  test->emit(codegen, frame_allocator, symbol_table);
  generate_test_jump(codegen, frame_allocator, symbol_table);
  generate_body(codegen, frame_allocator, symbol_table);
  generate_else(codegen, frame_allocator, symbol_table);
  codegen->GenLabel(after_stmt_label);
}

void IfStmt::generate_labels(CodeGenerator* codegen) {
  after_stmt_label = codegen->NewLabel();
  else_body_label = codegen->NewLabel();
  false_label = after_stmt_label;
  if (elseBody)
    false_label = else_body_label;
}

void IfStmt::generate_test_jump(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  test_location = test->get_frame_location();
  codegen->GenIfZ(test_location, false_label);
}

void IfStmt::generate_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  body->emit(codegen, frame_allocator, symbol_table);
  codegen->GenGoto(after_stmt_label);
}

void IfStmt::generate_else(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  if (elseBody) {
    codegen->GenLabel(else_body_label);
    elseBody->emit(codegen, frame_allocator, symbol_table);
    codegen->GenGoto(after_stmt_label);
  }
}
