#include "call.hh"

#include <algorithm>

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
  List<Type*> arg_types(actuals->NumElements());
  std::transform(actuals->begin(), actuals->end(),
                 arg_types.begin(), [&](Expr* arg) {
                   return arg->evaluate_type(symbol_table);
                 });
  if (base == nullptr) {
    symbol_table->check_function_declared(field, [&]() {
        ReportError::IdentifierNotDeclared(field, LookingForFunction);
      });
    auto good_length =
      symbol_table->check_function_args_length(field, actuals, [&](int expected, int given) {
          ReportError::NumArgsMismatch(field, expected, given);
        });
    if (!good_length)
      return;
    symbol_table->
      check_function_args(field,
                          actuals,
                          &arg_types,
                          [&](Expr* arg, int index, Type* expected, Type* given) {
                            ReportError::ArgMismatch(arg, index, expected, given);
                          });
  }
  else {
    auto base_type = base->evaluate_type(symbol_table);
    auto base_table = symbol_table->get_table_for_functions(base_type);
    base_table->check_function_declared(field, [&]() {
        ReportError::FieldNotFoundInBase(field, base_type);
      });
    auto good_length =
      base_table->check_function_args_length(field, actuals, [&](int expected, int given) {
        ReportError::NumArgsMismatch(field, expected, given);
      });
    if (!good_length)
      return;
    base_table->
      check_function_args(field,
                          actuals,
                          &arg_types,
                          [&](Expr* arg, int index, Type* expected, Type* given) {
                            ReportError::ArgMismatch(arg, index, expected, given);
                          });
  }
}
