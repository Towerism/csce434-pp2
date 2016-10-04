#ifndef POSTFIX_EXPR_H
#define POSTFIX_EXPR_H

#include "compound_expr.hh"

class PostfixExpr : public CompoundExpr {
public:
  PostfixExpr(Expr *lhs, Operator *op) : CompoundExpr(lhs, op) {}
  Type *evaluate_type(Symbol_table *symbol_table) override {
    return left->evaluate_type(symbol_table);
  }

  const char *GetPrintNameForNode() override { return "PostfixExpr"; }
};

#endif /* POSTFIX_EXPR_H */
