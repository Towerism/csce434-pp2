#include "field_access.hh"

#include <util/utility.hh>

#include <ast/symbol_table.hh>
#include <ast/decl/var_decl.hh>

FieldAccess::FieldAccess(Expr *b, Identifier *f)  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
  Assert(f != NULL); // b can be be NULL (just means no explicit base)
  base = b;
  if (base) base->SetParent(this);
  (field=f)->SetParent(this);
}

void FieldAccess::PrintChildren(int indentLevel) {
  if (base) base->Print(indentLevel+1);
  field->Print(indentLevel+1);
}

void FieldAccess::analyze(Symbol_table* symbol_table, reasonT focus) {
  if (base == nullptr)
    symbol_table->check_variable_declared(field, [&]() {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
      });
  else {
    auto base_type = base->evaluate_type(symbol_table);
    auto base_table = symbol_table->get_table_for_variables(base_type);
    if (!base_table) {
      ReportError::FieldNotFoundInBase(field, base_type);
      return;
    }
    base_table->check_variable_declared(field, [&]() {
        ReportError::FieldNotFoundInBase(field, base_type);
      });
    symbol_table->check_variable_declared(field, [&]() {
        ReportError::InaccessibleField(field, base_type);
      });
  }
}

Type* FieldAccess::evaluate_type(Symbol_table* symbol_table) {
  auto symbol = symbol_table->check_variable_declared(field);
  return symbol->get_type();
}
