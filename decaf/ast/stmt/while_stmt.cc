#include "while_stmt.hh"

#include <codegen/codegen.hh>

void WhileStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(body) ");
}

void WhileStmt::generate_before_stmt_end(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  codegen->GenGoto(before_stmt_label);
}
