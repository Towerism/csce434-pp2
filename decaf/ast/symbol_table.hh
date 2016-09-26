#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>

#include "declaration_table.hh"

class Decl;
class ClassDecl;
class InterfaceDecl;
class VarDecl;
class FnDecl;

class Symbol_table {
public:
  void declare(Decl* declaration);
  bool type_exists(std::string name);

  void check_super(Decl* declaration);
  void set_super(Symbol_table& super_table) { super = &super_table; }

  ClassDecl* get_class(std::string name);

private:
  Declaration_table<ClassDecl> classes;
  Declaration_table<InterfaceDecl> interfaces;
  Declaration_table<VarDecl> variables;
  Declaration_table<FnDecl> functions;

  Symbol_table* super = nullptr;

  void detect_previous_declaration(Decl* new_declaration);
};

#endif // SYMBOL_TABLE_H
