#ifndef RELATIONAL_EXPR_H
#define RELATIONAL_EXPR_H

#include "compound_expr.hh"

class RelationalExpr : public CompoundExpr {
public:
  RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  const char *GetPrintNameForNode() { return "RelationalExpr"; }
};

#endif /* RELATIONAL_EXPR_H */
