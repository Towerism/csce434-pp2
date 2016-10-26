#include "conditional_stmt.hh"

#include <codegen/codegen.hh>

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
  Assert(t != NULL && b != NULL);
  (test=t)->SetParent(this);    (body=b)->SetParent(this);
}

void ConditionalStmt::build_table() {
  body->build_table();
}

void ConditionalStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  test->analyze(symbol_table, focus);
  auto type = test->evaluate_type(symbol_table);
  if (!type->coerce(Type::boolType, symbol_table))
    ReportError::TestNotBoolean(test);
  body->analyze(symbol_table, focus);
}

void ConditionalStmt::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  generate_labels(codegen);
  generate_test_jump(codegen, frame_allocator, symbol_table);
  generate_body(codegen, frame_allocator, symbol_table);
}

void ConditionalStmt::generate_labels(CodeGenerator* codegen) {
  before_stmt_label = codegen->NewLabel();
  after_stmt_label = codegen->NewLabel();
  false_label = after_stmt_label;
  generate_extra_labels(codegen);
  codegen->GenLabel(before_stmt_label);
}

void ConditionalStmt::generate_test_jump(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  test->emit(codegen, frame_allocator, symbol_table);
  test_location = test->get_frame_location();
  codegen->GenIfZ(test_location, false_label);
}

void ConditionalStmt::generate_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  body->emit(codegen, frame_allocator, symbol_table);
  generate_after_body(codegen, frame_allocator, symbol_table);
  generate_before_stmt_end(codegen, frame_allocator, symbol_table);
  codegen->GenLabel(after_stmt_label);
}
