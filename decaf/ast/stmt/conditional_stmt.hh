#ifndef CONDITIONAL_STMT_H
#define CONDITIONAL_STMT_H

#include "stmt.hh"

#include <ast/symbol_table.hh>
#include <ast/expr/ast_expr.hh>

class ConditionalStmt : public Stmt
{
protected:
  Expr *test;
  Stmt *body;
  Symbol_table symbol_table;
public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
  virtual void build_table() override;
  virtual void analyze(reasonT focus) override;
};


#endif /* CONDITIONAL_STMT_H */
