#ifndef ARITHMETIC_EXPR_H
#define ARITHMETIC_EXPR_H

#include "compound_expr.hh"

class ArithmeticExpr : public CompoundExpr {
public:
  ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
  const char *GetPrintNameForNode() { return "ArithmeticExpr"; }
};

#endif /* ARITHMETIC_EXPR_H */
