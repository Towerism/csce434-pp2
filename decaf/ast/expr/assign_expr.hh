#ifndef ASSIGN_EXPR_H
#define ASSIGN_EXPR_H

#include "compound_expr.hh"

class AssignExpr : public CompoundExpr {
public:
  AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  const char *GetPrintNameForNode() { return "AssignExpr"; }
};

#endif /* ASSIGN_EXPR_H */
