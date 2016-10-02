#ifndef CONDITIONAL_STMT_H
#define CONDITIONAL_STMT_H

#include "stmt.hh"

#include <ast/symbol_table.hh>
#include <ast/expr/ast_expr.hh>

#include <iostream>
class ConditionalStmt : public Stmt
{
protected:
  Expr *test;
  Stmt *body;
  Symbol_table symbol_table;
public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
  virtual void build_table() override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void set_parent(Symbol_table& other) override { body->set_parent(other); }
};


#endif /* CONDITIONAL_STMT_H */
