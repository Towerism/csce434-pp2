#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>

#include "declaration_table.hh"

class Decl;
class ClassDecl;
class InterfaceDecl;
class VarDecl;

class Symbol_table {
public:
  void declare(Decl* declaration);
  void declare_class(ClassDecl* class_declaration);
  void declare_interface(InterfaceDecl* interface_declaration);
  void declare_variable(VarDecl* variable_declaration);
  bool type_exists(std::string name);

private:
  Declaration_table<ClassDecl> classes;
  Declaration_table<InterfaceDecl> interfaces;
  Declaration_table<VarDecl> variables;
};

#endif // SYMBOL_TABLE_H
