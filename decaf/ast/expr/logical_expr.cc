#include "logical_expr.hh"

#include <codegen/codegen.hh>

void LogicalExpr::analyze(Symbol_table *symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  Type *left_type;
  Type *right_type;
  if (left && right) {
    left_type = left->evaluate_type(symbol_table);
    right_type = right->evaluate_type(symbol_table);
    if (!left_type->equal(Type::boolType) || !right_type->equal(Type::boolType))
      ReportError::IncompatibleOperands(op, left_type, right_type);
  } else if (right) {
    right_type = right->evaluate_type(symbol_table);
    if (!right_type->equal(Type::boolType))
      ReportError::IncompatibleOperand(op, right_type);
  }
}

void LogicalExpr::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                       Symbol_table *symbol_table) {
  CompoundExpr::emit(codegen, frame_allocator, symbol_table);
  Location *right_location = right->get_frame_location();
  if (left) {
    Location *left_location = left->get_frame_location();
    frame_location = codegen->GenBinaryOp(op->get_token_string(), left_location,
                                          right_location, frame_allocator);
  } else {
    frame_location = codegen->GenNot(right_location, frame_allocator);
  }
}
