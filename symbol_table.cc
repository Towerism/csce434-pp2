#include "symbol_table.hh"

#include <algorithm>

#include "ast_decl.hh"
#include "errors.hh"

void Symbol_table::declare(Decl* declaration) {
  detect_previous_declaration(declaration);
  auto class_declaration = dynamic_cast<ClassDecl*>(declaration);
  if (class_declaration != nullptr) {
    classes.declare(class_declaration);
    return;
  }
  auto interface_declaration = dynamic_cast<InterfaceDecl*>(declaration);
  if (interface_declaration != nullptr) {
    interfaces.declare(interface_declaration);
    return;
  }
  auto variable_declaration = dynamic_cast<VarDecl*>(declaration);
  if (variable_declaration != nullptr) {
    variables.declare(variable_declaration);
    return;
  }
  auto function_declaration = dynamic_cast<FnDecl*>(declaration);
  if (function_declaration != nullptr) {
    functions.declare(function_declaration);
    return;
  }
}

void Symbol_table::detect_previous_declaration(Decl* new_declaration) {
  Decl* prev_decl = variables.contains(new_declaration->getName());
  if (!prev_decl) {
    prev_decl = functions.contains(new_declaration->getName());
  }
  if (!prev_decl)
    prev_decl = classes.contains(new_declaration->getName());
  if (!prev_decl)
    prev_decl = interfaces.contains(new_declaration->getName());
  if (prev_decl)
    ReportError::DeclConflict(new_declaration, prev_decl);
}

void Symbol_table::check_super(Decl* declaration) {
  auto* function = dynamic_cast<FnDecl*>(declaration);
  if (!function)
    return;
  if (!super)
    return;
  auto* current = super;
  do {
    auto* super_function = current->functions.contains(function->getName());
    if (super_function && !function->matches_signature(super_function))
      ReportError::OverrideMismatch(function);
    current = current->super;
  } while(current != nullptr);
}

bool Symbol_table::type_exists(std::string name) {
  return classes.contains(name) || interfaces.contains(name);
}

ClassDecl* Symbol_table::get_class(std::string name) {
  return classes.contains(name);
}
