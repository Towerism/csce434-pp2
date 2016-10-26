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
  accessing_table = symbol_table;
  if (base)
    access_on_base();
  else
    access_on_scope();
}

void FieldAccess::access_on_base() {
  base_type = base->evaluate_type(accessing_table);
  base_table = accessing_table->get_table_for_variables(base_type);
  check_field_on_base_accessibility();
}

void FieldAccess::access_on_scope() {
  accessing_table->check_variable_declared(field, [&]() {
      ReportError::IdentifierNotDeclared(field, LookingForVariable);
    });
}

void FieldAccess::check_field_on_base_accessibility() {
  if (!base_table_exists())
    return;
  if (field_is_not_in_base())
    check_if_field_is_inaccessible();
}

bool FieldAccess::base_table_exists() {
  if (!base_table) {
    ReportError::FieldNotFoundInBase(field, base_type);
    return false;
  }
  return true;
}

bool FieldAccess::field_is_not_in_base() {
  auto variable = base_table->check_variable_declared(field, [&]() {
      ReportError::FieldNotFoundInBase(field, base_type);
    });
  return variable->getType() != Type::errorType;
}

void FieldAccess::check_if_field_is_inaccessible() {
  accessing_table->check_variable_declared(field, [&]() {
      ReportError::InaccessibleField(field, base_type);
    });
}

Type* FieldAccess::evaluate_type(Symbol_table* symbol_table) {
  VarDecl* variable = nullptr;
  if (!base) {
    variable = symbol_table->check_variable_declared(field, [&]() {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
      });
  } else {
    auto base_type = base->evaluate_type(symbol_table);
    auto base_table = symbol_table->get_table_for_functions(base_type);
    if (base_table)
      variable = base_table->check_variable_declared(field), [&]() {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
      };
  }
  if (!variable)
    return Type::errorType;
  return variable->get_type();
}

void FieldAccess::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  if (!base) {
    auto variable = symbol_table->check_variable_declared(field);
    auto location = variable->get_frame_location();
    frame_location = location;
  }
}
