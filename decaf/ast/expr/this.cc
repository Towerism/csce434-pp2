#include "this.hh"

#include <util/errors.hh>

#include <ast/decl/var_decl.hh>
#include <ast/symbol_table.hh>

#include <codegen/codegen.hh>

#include <iostream>
void This::analyze(Symbol_table *symbol_table, reasonT focus) {
  auto type = evaluate_type(symbol_table);
  if (type == Type::errorType) {
    ReportError::ThisOutsideClassScope(this);
  }
}

Type *This::evaluate_type(Symbol_table *symbol_table) {
  auto type = symbol_table->find_this_type();
  if (!type)
    return Type::errorType;
  return type;
}

void This::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                Symbol_table *symbol_table) {
  if (!frame_location)
    frame_location = CodeGenerator::ThisPtr;
}
