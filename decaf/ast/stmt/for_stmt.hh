#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "loop_stmt.hh"

class ForStmt : public LoopStmt{
protected:
  Expr *init, *step;
public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  const char *GetPrintNameForNode() override { return "ForStmt"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void generate_before_begin_label(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
  void generate_after_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
};

#endif /* FOR_STMT_H */
