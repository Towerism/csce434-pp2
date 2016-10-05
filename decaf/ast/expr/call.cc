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
  arg_types = List<Type*>(actuals->NumElements());
}

void Call::PrintChildren(int indentLevel) {
  if (base) base->Print(indentLevel+1);
  field->Print(indentLevel+1);
  actuals->PrintAll(indentLevel+1, "(actuals) ");
}

void Call::analyze(Symbol_table* symbol_table, reasonT focus) {
  calling_table = symbol_table;
  initialize_arg_types();
  if (base)
    call_on_base();
  else
    call_on_scope();
}

void Call::initialize_arg_types() {
  std::transform(actuals->begin(), actuals->end(),
                 arg_types.begin(), [&](Expr* arg) {
                   return arg->evaluate_type(calling_table);
                 });
}

void Call::call_on_base() {
    base_type = base->evaluate_type(calling_table);
    if (call_is_to_primitive_or_array_length())
      return;
    check_args_length_and_types();
}

bool Call::call_is_to_primitive_or_array_length() {
  auto array_type = dynamic_cast<ArrayType*>(base_type);
  if (array_type && field->getName() == "length" && actuals->NumElements() == 0)
    return true;
  if (array_type || base_type->is_primitive()) {
    ReportError::FieldNotFoundInBase(field, base_type);
    return true;
  }
  return false;
}

void Call::check_args_length_and_types() {
  base_table = calling_table->get_table_for_functions(base_type);
  if (!base_table) {
    return;
  }
  base_table->check_function_declared(field, [&]() {
      ReportError::FieldNotFoundInBase(field, base_type);
    });
  if (!args_length_is_good(base_table)) {
    return;
  }
  check_args_types(base_table);
}

bool Call::args_length_is_good(Symbol_table* table_for_function) {
  return table_for_function->
    check_function_args_length(field, actuals,
                               [&](int expected, int given) {
                                 ReportError::NumArgsMismatch(field, expected, given);
                               });
}

void Call::check_args_types(Symbol_table* table_for_function) {
  table_for_function->
    check_function_args(field,
                        actuals,
                        &arg_types,
                        [&](Expr* arg, int index, Type* expected, Type* given) {
                          ReportError::ArgMismatch(arg, index, expected, given);
                        });
}

void Call::call_on_scope() {
  calling_table->check_function_declared(field, [&]() {
      ReportError::IdentifierNotDeclared(field, LookingForFunction);
      return;
    });
  if (args_length_is_good(calling_table))
    check_args_types(calling_table);
}

Type* Call::evaluate_type(Symbol_table* symbol_table) {
  FnDecl* function = nullptr;
  if (!base) {
    function = symbol_table->check_function_declared(field);
  } else {
    auto base_type = base->evaluate_type(symbol_table);
    auto base_table = symbol_table->get_table_for_functions(base_type);
    if (base_table)
      function = base_table->check_function_declared(field);
  }
  if (!function)
    return Type::errorType;
  return function->get_type();
}
