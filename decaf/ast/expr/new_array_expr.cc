#include "new_array_expr.hh"

#include <util/utility.hh>

#include <ast/stmt/program.hh>
#include <ast/symbol_table.hh>
#include <ast/type/array_type.hh>

#include <codegen/codegen.hh>
#include <codegen/frame_allocator.hh>

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
  Assert(sz != NULL && et != NULL);
  (size = sz)->SetParent(this);
  (elemType = et)->SetParent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) {
  size->Print(indentLevel + 1);
  elemType->Print(indentLevel + 1);
}

void NewArrayExpr::analyze(Symbol_table *symbol_table, reasonT focus) {
  auto size_type = size->evaluate_type(symbol_table);
  if (!size_type->coerce(Type::intType, symbol_table))
    ReportError::NewArraySizeNotInteger(size);
  elemType->verify(LookingForType);
}

Type *NewArrayExpr::evaluate_type(Symbol_table *symbol_table) {
  return new ArrayType(yyltype(), elemType);
}

void NewArrayExpr::emit(CodeGenerator *codegen,
                        Frame_allocator *frame_allocator,
                        Symbol_table *symbol_table) {
  size->emit(codegen, frame_allocator, symbol_table);
  size_location = size->get_frame_location();
  emit_size_check(codegen, frame_allocator, symbol_table);
  emit_size_calculation(codegen, frame_allocator, symbol_table);
  emit_allocation(codegen, frame_allocator, symbol_table);
}

void NewArrayExpr::emit_size_check(CodeGenerator *codegen,
                                   Frame_allocator *frame_allocator,
                                   Symbol_table *symbol_table) {
  auto after_error_label = codegen->NewLabel();
  auto zero = codegen->GenLoadConstant(0, frame_allocator);
  auto size_comparison =
      codegen->GenComplexBinaryOp("<=", size_location, zero, frame_allocator);
  codegen->GenIfZ(size_comparison, after_error_label);
  codegen->GenRuntimeError(Runtime_error::Array_size, frame_allocator);
  codegen->GenLabel(after_error_label);

  frame_location = frame_allocator->allocate(4, strdup("size"));
}

void NewArrayExpr::emit_size_calculation(CodeGenerator *codegen,
                                         Frame_allocator *frame_allocator,
                                         Symbol_table *symbol_table) {
  auto one_for_size = codegen->GenLoadConstant(1, frame_allocator);
  auto four_for_word = codegen->GenLoadConstant(4, frame_allocator);
  auto array_size_plus_one =
      codegen->GenBinaryOp("+", size_location, one_for_size, frame_allocator);
  size_needed_in_bytes = codegen->GenBinaryOp("*", array_size_plus_one,
                                              four_for_word, frame_allocator);
}

void NewArrayExpr::emit_allocation(CodeGenerator *codegen,
                                   Frame_allocator *frame_allocator,
                                   Symbol_table *symbol_table) {
  frame_location = codegen->GenBuiltInCall(Alloc, frame_allocator, size_needed_in_bytes);
  codegen->GenStore(frame_location, size_location);
}
