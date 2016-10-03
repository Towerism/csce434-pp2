#include "new_array_expr.hh"

#include <util/utility.hh>

#include <ast/symbol_table.hh>
#include <ast/type/array_type.hh>

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
}

Type *NewArrayExpr::evaluate_type(Symbol_table *symbol_table) {
  return new ArrayType(yyltype(), elemType);
}
