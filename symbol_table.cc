#include "symbol_table.hh"

#include <algorithm>

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
  auto function_declaration = dynamic_cast<FnDecl*>(declaration);
  if (function_declaration != nullptr) {
    declare_function(function_declaration);
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

void Symbol_table::declare_function(FnDecl* function_declaration) {
  Decl* prev_decl = variables.contains(function_declaration->getName());
  if (!prev_decl) {
    prev_decl = functions.contains(function_declaration->getName());
  }
  if (prev_decl)
    ReportError::DeclConflict(function_declaration, prev_decl);
  functions.declare(function_declaration);
}

void Symbol_table::copy_fields_into(Symbol_table& sub_table) {
  std::for_each(variables.begin(), variables.end(), [&](std::pair<std::string, VarDecl*> pair) {
      sub_table.declare(pair.second);
    });
  std::for_each(functions.begin(), functions.end(), [&](std::pair<std::string, FnDecl*> pair) {
      sub_table.declare(pair.second);
    });
}

bool Symbol_table::type_exists(std::string name) {
  return classes.contains(name) || interfaces.contains(name);
}

ClassDecl* Symbol_table::get_class(std::string name) {
  return classes.contains(name);
}
