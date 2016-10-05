#include "return_stmt.hh"

#include <util/utility.hh>

#include <ast/symbol_table.hh>

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) {
  Assert(e != NULL);
  (expr=e)->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) {
  expr->Print(indentLevel+1);
}

void ReturnStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  auto expected_return_type = symbol_table->find_return_type();
  auto return_type = expr->evaluate_type(symbol_table);
  if (!return_type->coerce(expected_return_type, symbol_table))
    ReportError::ReturnMismatch(this, return_type, expected_return_type);
}

yyltype* ReturnStmt::get_expr_location() {
  return expr->get_location_or_default(location);
}
