#include "array_access.hh"

#include <ast/symbol_table.hh>
#include <ast/type/array_type.hh>

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
  (base=b)->SetParent(this);
  (subscript=s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
  base->Print(indentLevel+1);
  subscript->Print(indentLevel+1, "(subscript) ");
}

void ArrayAccess::analyze(Symbol_table* symbol_table, reasonT focus) {
  base->analyze(symbol_table, focus);
  subscript->analyze(symbol_table, focus);
  auto base_type = base->evaluate_type(symbol_table);
  auto array_type = dynamic_cast<ArrayType*>(base_type);
  if (!array_type && base_type != Type::errorType)
    ReportError::BracketsOnNonArray(base);
  auto subscript_type = subscript->evaluate_type(symbol_table);
  if (!subscript_type->coerce(Type::intType, symbol_table))
    ReportError::SubscriptNotInteger(subscript);
}
