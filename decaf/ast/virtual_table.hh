#ifndef VIRTUAL_TABLE_H
#define VIRTUAL_TABLE_H

#include <unordered_map>

#include "declaration_table.hh"

class FnDecl;
class NamedType;

class Virtual_table {
public:
  void add(std::string interface_name, FnDecl* function);
  FnDecl* contains(std::string function_name);
  Declaration_table<FnDecl>* get_functions(std::string interface_name);

private:
  std::unordered_map<std::string, Declaration_table<FnDecl>*> virtuals;
};

#endif /* VIRTUAL_TABLE_H */
