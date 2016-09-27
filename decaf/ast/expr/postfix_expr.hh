#ifndef POSTFIX_EXPR_H
#define POSTFIX_EXPR_H

#include "compound_expr.hh"

class PostfixExpr : public CompoundExpr {
public:
  PostfixExpr(Expr *lhs, Operator *op) : CompoundExpr(lhs, op) {}

  const char *GetPrintNameForNode() { return "PostfixExpr"; }
};

#endif /* POSTFIX_EXPR_H */
