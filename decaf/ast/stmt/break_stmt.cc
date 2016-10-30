#include "break_stmt.hh"

void BreakStmt::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                     Symbol_table *symbol_table) {
  Node *current = this;
  do {
    if (current->break_now(codegen, frame_allocator, symbol_table))
      return;
    current = current->get_parent();
  } while (current != nullptr);
}
