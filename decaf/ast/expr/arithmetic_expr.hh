#ifndef ARITHMETIC_EXPR_H
#define ARITHMETIC_EXPR_H

#include "compound_expr.hh"

class ArithmeticExpr : public CompoundExpr {
public:
  ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
  const char *GetPrintNameForNode() override { return "ArithmeticExpr"; }
  void analyze(Symbol_table* symbol_table, reasonT focus) override {
    CompoundExpr::analyze(symbol_table, focus);
    auto left_type = left->evaluate_type(symbol_table);
    auto right_type = right->evaluate_type(symbol_table);
    if ((!left_type->equal(Type::intType) && !left_type->equal(Type::doubleType))
        || !left_type->equal(right_type))
      ReportError::IncompatibleOperands(op, left_type, right_type);
  }
};

#endif /* ARITHMETIC_EXPR_H */
