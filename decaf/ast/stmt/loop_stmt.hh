#ifndef LOOP_STMT_H
#define LOOP_STMT_H

#include "conditional_stmt.hh"

#include <ast/expr/ast_expr.hh>

class LoopStmt : public ConditionalStmt{
public:
  LoopStmt(Expr *testExpr, Stmt *body)
    : ConditionalStmt(testExpr, body) {
    is_break_node = true;
  }

  bool break_now(CodeGenerator *codegen, Frame_allocator *frame_allocator, Symbol_table *symbol_table) override;
};


#endif /* LOOP_STMT_H */
