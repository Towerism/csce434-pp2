#include "array_access.hh"

#include <ast/symbol_table.hh>
#include <ast/type/array_type.hh>

#include <codegen/codegen.hh>

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
  (base = b)->SetParent(this);
  (subscript = s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
  base->Print(indentLevel + 1);
  subscript->Print(indentLevel + 1, "(subscript) ");
}

void ArrayAccess::analyze(Symbol_table *symbol_table, reasonT focus) {
  base->analyze(symbol_table, focus);
  subscript->analyze(symbol_table, focus);
  auto base_type = base->evaluate_type(symbol_table);
  auto array_type = dynamic_cast<ArrayType *>(base_type);
  if (!array_type && base_type != Type::errorType)
    ReportError::BracketsOnNonArray(base);
  auto subscript_type = subscript->evaluate_type(symbol_table);
  if (!subscript_type->coerce(Type::intType, symbol_table))
    ReportError::SubscriptNotInteger(subscript);
}

Type *ArrayAccess::evaluate_type(Symbol_table *symbol_table) {
  auto array_type = base->evaluate_type(symbol_table);
  return array_type->get_elem_type();
}

void ArrayAccess::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                       Symbol_table *symbol_table) {
  calculate_locations(codegen, frame_allocator, symbol_table);
  emit_subscript_check(codegen, frame_allocator, symbol_table);
  emit_frame_location(codegen, frame_allocator, symbol_table);
}

void ArrayAccess::calculate_locations(CodeGenerator *codegen,
                                      Frame_allocator *frame_allocator,
                                      Symbol_table *symbol_table) {
  base->emit(codegen, frame_allocator, symbol_table);
  subscript->emit(codegen, frame_allocator, symbol_table);
  base_location = base->get_frame_location();
  subscript_location = subscript->get_frame_location();
}

void ArrayAccess::emit_subscript_check(CodeGenerator *codegen,
                                       Frame_allocator *frame_allocator,
                                       Symbol_table *symbol_table) {
  after_error_label = codegen->NewLabel();
  auto zero = codegen->GenLoadConstant(0, frame_allocator);
  auto size = codegen->GenLoad(base_location, frame_allocator);
  auto less_than_zero =
      codegen->GenBinaryOp("<", subscript_location, zero, frame_allocator);
  auto geq_than_size = codegen->GenComplexBinaryOp(">=", subscript_location,
                                                   size, frame_allocator);
  auto size_check = codegen->GenBinaryOp("||", less_than_zero, geq_than_size,
                                         frame_allocator);
  codegen->GenIfZ(size_check, after_error_label);
  codegen->GenRuntimeError(Runtime_error::Array_subscript, frame_allocator);
  codegen->GenLabel(after_error_label);
}

void ArrayAccess::emit_frame_location(CodeGenerator *codegen,
                                      Frame_allocator *frame_allocator,
                                      Symbol_table *symbol_table) {
  auto one = codegen->GenLoadConstant(1, frame_allocator);
  auto four = codegen->GenLoadConstant(4, frame_allocator);
  auto offset_from_base =
      codegen->GenBinaryOp("+", subscript_location, one, frame_allocator);
  auto offset_in_bytes =
    codegen->GenBinaryOp("*", offset_from_base, four, frame_allocator);
  reference = codegen->GenBinaryOp("+", base_location, offset_in_bytes,
                                   frame_allocator);
  frame_location = codegen->GenLoad(reference, frame_allocator);
}
