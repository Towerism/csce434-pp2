#include "logical_expr.hh"

void LogicalExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  Type* left_type;
  Type* right_type;
  if (left && right) {
    left_type = left->evaluate_type(symbol_table);
    right_type = left->evaluate_type(symbol_table);
    if (!left_type->equal(Type::boolType) || !right_type->equal(Type::boolType))
      ReportError::IncompatibleOperands(op, left_type, right_type);
  } else if (right) {
    right_type = right->evaluate_type(symbol_table);
    if (!right_type->equal(Type::boolType))
      ReportError::IncompatibleOperand(op, right_type);
  }
}
