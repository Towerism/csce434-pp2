#ifndef WHILE_STMT_H
#define WHILE_STMT_H

#include "loop_stmt.hh"

class WhileStmt : public LoopStmt{
public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  const char *GetPrintNameForNode() override { return "WhileStmt"; }
  void PrintChildren(int indentLevel) override;
protected:
  void generate_before_stmt_end(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
};

#endif /* WHILE_STMT_H */
