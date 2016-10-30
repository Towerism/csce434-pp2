#ifndef BREAK_STMT_H
#define BREAK_STMT_H

#include "stmt.hh"

class BreakStmt : public Stmt {
public:
  BreakStmt(yyltype loc) : Stmt(loc) {}
  const char *GetPrintNameForNode() override { return "BreakStmt"; }
  void analyze(Symbol_table *symbol_table, reasonT focus) override {
    if (!find_loop_node())
      ReportError::BreakOutsideLoop(this);
  }

  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;
};

#endif /* BREAK_STMT_H */
