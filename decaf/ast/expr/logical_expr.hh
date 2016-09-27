#ifndef LOGICAL_EXPR_H
#define LOGICAL_EXPR_H

#include "compound_expr.hh"

class LogicalExpr : public CompoundExpr {
public:
  LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
  const char *GetPrintNameForNode() { return "LogicalExpr"; }
};

#endif /* LOGICAL_EXPR_H */
