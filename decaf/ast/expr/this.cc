#include "this.hh"

#include <util/errors.hh>

#include <ast/symbol_table.hh>

void This::analyze(Symbol_table* symbol_table, reasonT focus) {
  evaluate_type(symbol_table);
}

Type* This::evaluate_type(Symbol_table* symbol_table) {
  auto type = symbol_table->find_this_type();
  if (!type)
    ReportError::ThisOutsideClassScope(this);
  return type;
}
