#ifndef RELATIONAL_EXPR_H
#define RELATIONAL_EXPR_H

#include "compound_expr.hh"

class RelationalExpr : public CompoundExpr {
public:
  RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  const char *GetPrintNameForNode() override { return "RelationalExpr"; }
  void analyze(Symbol_table* symbol_table, reasonT focus) override {
    auto left_type = left->evaluate_type(symbol_table);
    auto right_type = right->evaluate_type(symbol_table);
    if (!left_is_compatible_with_right(symbol_table))
      ReportError::IncompatibleOperands(op, left_type, right_type);
  }
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::boolType; }
};

#endif /* RELATIONAL_EXPR_H */
