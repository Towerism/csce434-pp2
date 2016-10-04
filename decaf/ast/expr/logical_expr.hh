#ifndef LOGICAL_EXPR_H
#define LOGICAL_EXPR_H

#include "compound_expr.hh"

#include <iostream>

#include <ast/type/type.hh>

class LogicalExpr : public CompoundExpr {
public:
  LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
  const char *GetPrintNameForNode() override { return "LogicalExpr"; }
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::boolType; }
};

#endif /* LOGICAL_EXPR_H */
