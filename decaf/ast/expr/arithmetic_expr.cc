#include "arithmetic_expr.hh"

#include <codegen/codegen.hh>

void ArithmeticExpr::analyze(Symbol_table *symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  Type *left_type;
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

Type *ArithmeticExpr::evaluate_type(Symbol_table *symbol_table) {
  if (left_is_compatible_with_right(symbol_table))
    return right->evaluate_type(symbol_table);
  return Type::errorType;
}

void ArithmeticExpr::emit(CodeGenerator *codegen,
                          Frame_allocator *frame_allocator,
                          Symbol_table *symbol_table) {
  CompoundExpr::emit(codegen, frame_allocator, symbol_table);
  Location *right_location = right->get_frame_location();
  if (left) {
    Location *left_location = left->get_frame_location();
    frame_location = codegen->GenBinaryOp(op->get_token_string(), left_location,
                                          right_location, frame_allocator);
  } else {
    auto zero = codegen->GenLoadConstant(0, frame_allocator);
    frame_location =
        codegen->GenBinaryOp("-", zero, right_location, frame_allocator);
  }
}
