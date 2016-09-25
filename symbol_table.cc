#include "symbol_table.hh"

#include <iostream>

#include "ast_decl.hh"

void Symbol_table::declare(Decl* declaration) {
  auto d = dynamic_cast<ClassDecl*>(declaration);
  if (d != nullptr) {
    declare_class(d);
    return;
  }
}

void Symbol_table::declare_class(ClassDecl* class_declaration) {
  std::string name = class_declaration->getName();
  class_declarations[name] = class_declaration;
}

ClassDecl* Symbol_table::class_exists(std::string name) {
  auto key_value = class_declarations.find(name);
  if (key_value != class_declarations.end())
    return key_value->second;
  return nullptr;
}
