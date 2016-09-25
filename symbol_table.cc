#include "symbol_table.hh"

#include <iostream>

#include "ast_decl.hh"
#include "errors.hh"

void Symbol_table::declare(Decl* declaration) {
  auto class_declaration = dynamic_cast<ClassDecl*>(declaration);
  if (class_declaration != nullptr) {
    declare_class(class_declaration);
    return;
  }
  auto interface_declaration = dynamic_cast<InterfaceDecl*>(declaration);
  if (interface_declaration != nullptr) {
    declare_interface(interface_declaration);
    return;
  }
  auto variable_declaration = dynamic_cast<VarDecl*>(declaration);
  if (variable_declaration != nullptr) {
    declare_variable(variable_declaration);
    return;
  }
}

void Symbol_table::declare_class(ClassDecl* class_declaration) {
  auto* prev_decl = classes.contains(class_declaration->getName());
  if (prev_decl)
    ReportError::DeclConflict(class_declaration, prev_decl);
  classes.declare(class_declaration);
}

void Symbol_table::declare_interface(InterfaceDecl* interface_declaration) {
  auto* prev_decl = interfaces.contains(interface_declaration->getName());
  if (prev_decl)
    ReportError::DeclConflict(interface_declaration, prev_decl);
  interfaces.declare(interface_declaration);
}

void Symbol_table::declare_variable(VarDecl* variable_declaration) {
  Decl* prev_decl = variables.contains(variable_declaration->getName());
  if (!prev_decl)
    prev_decl = classes.contains(variable_declaration->getName());
  if (prev_decl)
    ReportError::DeclConflict(variable_declaration, prev_decl);
  variables.declare(variable_declaration);
}

bool Symbol_table::type_exists(std::string name) {
  return classes.contains(name) || interfaces.contains(name);
}
