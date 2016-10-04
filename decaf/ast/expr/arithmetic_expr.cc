#include "arithmetic_expr.hh"

void ArithmeticExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  auto left_type = left->evaluate_type(symbol_table);
  auto right_type = right->evaluate_type(symbol_table);
  if ((!left_type->equal(Type::intType) && !left_type->equal(Type::doubleType))
      || !left_type->equal(right_type))
    ReportError::IncompatibleOperands(op, left_type, right_type);
}

Type* ArithmeticExpr::evaluate_type(Symbol_table* symbol_table) {
  if (left)
    return left->evaluate_type(symbol_table);
  return right->evaluate_type(symbol_table);
}
