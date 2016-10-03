#ifndef EQUALITY_EXPR_H
#define EQUALITY_EXPR_H

#include "compound_expr.hh"

class EqualityExpr : public CompoundExpr {
public:
  EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  const char *GetPrintNameForNode() override { return "EqualityExpr"; }
  void analyze(Symbol_table* symbol_table, reasonT focus) override {
    auto left_type = left->evaluate_type(symbol_table);
    auto right_type = right->evaluate_type(symbol_table);
    if (!left_type->equal(right_type))
      ReportError::IncompatibleOperands(op, left_type, right_type);
  }
};

#endif /* EQUALITY_EXPR_H */
