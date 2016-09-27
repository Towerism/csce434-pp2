#ifndef EQUALITY_EXPR_H
#define EQUALITY_EXPR_H

#include "compound_expr.hh"

class EqualityExpr : public CompoundExpr {
public:
  EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  const char *GetPrintNameForNode() { return "EqualityExpr"; }
};

#endif /* EQUALITY_EXPR_H */
