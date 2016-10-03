#include "call.hh"

#include <util/utility.hh>

#include <ast/symbol_table.hh>

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
  Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
  base = b;
  if (base) base->SetParent(this);
  (field=f)->SetParent(this);
  (actuals=a)->SetParentAll(this);
}

void Call::PrintChildren(int indentLevel) {
  if (base) base->Print(indentLevel+1);
  field->Print(indentLevel+1);
  actuals->PrintAll(indentLevel+1, "(actuals) ");
}

void Call::analyze(Symbol_table* symbol_table, reasonT focus) {
  if (base == nullptr) {
    symbol_table->check_function_declared(field, [&]() {
        ReportError::IdentifierNotDeclared(field, LookingForFunction);
      });
    symbol_table->check_function_args_length(field, actuals, [&](int expected, int given) {
        ReportError::NumArgsMismatch(field, expected, given);
      });
  }
  else {
    auto base_type = base->evaluate_type(symbol_table);
    auto base_table = symbol_table->get_table_for_functions(base_type);
    base_table->check_function_declared(field, [&]() {
        ReportError::FieldNotFoundInBase(field, base_type);
      });
    base_table->check_function_args_length(field, actuals, [&](int expected, int given) {
        ReportError::NumArgsMismatch(field, expected, given);
      });
  }
}
