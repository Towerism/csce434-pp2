#include "relational_expr.hh"

#include <codegen/codegen.hh>

void RelationalExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  auto left_type = left->evaluate_type(symbol_table);
  auto right_type = right->evaluate_type(symbol_table);
  if (!left_is_compatible_with_right(symbol_table))
    ReportError::IncompatibleOperands(op, left_type, right_type);
}

void RelationalExpr::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  CompoundExpr::emit(codegen, frame_allocator, symbol_table);
  Location* left_location = left->get_frame_location();
  Location* right_location = right->get_frame_location();
  frame_location = codegen->GenComplexBinaryOp(op->get_token_string(), left_location, right_location, frame_allocator);
}
