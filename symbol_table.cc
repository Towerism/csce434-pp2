#include "symbol_table.hh"

#include <iostream>

#include "ast_decl.hh"

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
}

void Symbol_table::declare_class(ClassDecl* class_declaration) {
  std::string name = class_declaration->getName();
  class_declarations[name] = class_declaration;
}

void Symbol_table::declare_interface(InterfaceDecl* interface_declaration) {
  std::string name = interface_declaration->getName();
  interface_declarations[name] = interface_declaration;
}

bool Symbol_table::type_exists(std::string name) {
  return class_exists(name) || interface_exists(name);
}

bool Symbol_table::class_exists(std::string name) {
  auto key_value = class_declarations.find(name);
  return key_value != class_declarations.end();
}

bool Symbol_table::interface_exists(std::string name) {
  auto key_value = interface_declarations.find(name);
  return key_value != interface_declarations.end();
}
