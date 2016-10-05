#include "arithmetic_expr.hh"

void ArithmeticExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  Type* left_type;
  if (left)
    left_type = left->evaluate_type(symbol_table);
  auto right_type = right->evaluate_type(symbol_table);
  if (!left_is_compatible_with_right(symbol_table)) {
    if (left)
      ReportError::IncompatibleOperands(op, left_type, right_type);
    else
      ReportError::IncompatibleOperand(op, right_type);
  }
}

Type* ArithmeticExpr::evaluate_type(Symbol_table* symbol_table) {
  if (left_is_compatible_with_right(symbol_table))
    return right->evaluate_type(symbol_table);
  return Type::errorType;
}
