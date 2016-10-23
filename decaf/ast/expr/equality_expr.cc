#include "equality_expr.hh"

#include <codegen/codegen.hh>
void EqualityExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  CompoundExpr::analyze(symbol_table, focus);
  auto left_type = left->evaluate_type(symbol_table);
  auto right_type = right->evaluate_type(symbol_table);
  if (!left_type->equal(right_type))
    ReportError::IncompatibleOperands(op, left_type, right_type);
}

void EqualityExpr::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  CompoundExpr::emit(codegen, frame_allocator, symbol_table);
  Location* left_location = left->get_frame_location();
  Location* right_location = right->get_frame_location();
  frame_location = codegen->GenComplexBinaryOp(op->get_token_string(), left_location, right_location, frame_allocator);
}
