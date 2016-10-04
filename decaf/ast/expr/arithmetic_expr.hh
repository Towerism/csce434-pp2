#ifndef ARITHMETIC_EXPR_H
#define ARITHMETIC_EXPR_H

#include "compound_expr.hh"

class ArithmeticExpr : public CompoundExpr {
public:
  ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
  const char *GetPrintNameForNode() override { return "ArithmeticExpr"; }
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  Type* evaluate_type(Symbol_table*) override;
};

#endif /* ARITHMETIC_EXPR_H */
