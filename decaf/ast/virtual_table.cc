#include "virtual_table.hh"

#include <ast/decl/fn_decl.hh>

void Virtual_table::add(std::string interface_name, FnDecl* function) {
  auto it = virtuals.find(interface_name);
  if (it == virtuals.end())
    virtuals[interface_name] = new Declaration_table<FnDecl>;
  virtuals[interface_name]->declare(function);
}

FnDecl* Virtual_table::contains(std::string function_name) {
  for (auto declaration_table : virtuals) {
    auto function = declaration_table.second->contains(function_name);
    if (function)
      return function;
  }
  return nullptr;
}

Declaration_table<FnDecl>* Virtual_table::get_functions(std::string interface_name) {
  auto it = virtuals.find(interface_name);
  if (it == virtuals.end())
    return nullptr;
  return virtuals[interface_name];
}
