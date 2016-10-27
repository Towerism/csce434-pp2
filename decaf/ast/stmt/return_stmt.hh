#ifndef RETURN_STMT_H
#define RETURN_STMT_H

#include "stmt.hh"

#include <ast/expr/ast_expr.hh>

class ReturnStmt : public Stmt{
protected:
  Expr *expr;
public:
  ReturnStmt(yyltype loc, Expr *expr);
  const char *GetPrintNameForNode() override { return "ReturnStmt"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  yyltype* get_expr_location();
  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;
};

#endif /* RETURN_STMT_H */
