#include "loop_stmt.hh"

#include <codegen/codegen.hh>

bool LoopStmt::break_now(CodeGenerator *codegen, Frame_allocator *frame_allocator, Symbol_table *symbol_table) {
  codegen->GenGoto(after_stmt_label);

  return true;
}
