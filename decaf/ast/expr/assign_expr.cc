#include "assign_expr.hh"

void AssignExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  auto left_type = left->evaluate_type(symbol_table);
  auto right_type = right->evaluate_type(symbol_table);
  if (!right_type->coerce(left_type, symbol_table))
    ReportError::IncompatibleOperands(op, left_type, right_type);
}
