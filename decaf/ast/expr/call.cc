#include "call.hh"

#include <algorithm>

#include <util/utility.hh>
#include <ast/symbol_table.hh>
#include <ast/decl/fn_decl.hh>

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
    auto array_type = dynamic_cast<ArrayType*>(base_type);
    if (array_type && field->getName() == "length" && actuals->NumElements() == 0)
      return;
    auto base_table = symbol_table->get_table_for_functions(base_type);
    if (array_type || base_type->equal(Type::intType)
        || base_type->equal(Type::stringType)
        || base_type->equal(Type::doubleType)
        || base_type->equal(Type::boolType)) {
      ReportError::FieldNotFoundInBase(field, base_type);
      return;
    }
    if (!base_table) {
      return;
    }
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

Type* Call::evaluate_type(Symbol_table* symbol_table) {
  FnDecl* function;
  if (base == nullptr) {
    function = symbol_table->check_function_declared(field);
  } else {
    auto base_type = base->evaluate_type(symbol_table);
    auto base_table = symbol_table->get_table_for_functions(base_type);
    function = base_table->check_function_declared(field);
  }
  if (!function)
    return Type::errorType;
  return function->get_type();
}
