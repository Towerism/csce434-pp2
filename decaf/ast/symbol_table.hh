#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>

#include "declaration_table.hh"
#include "virtual_table.hh"

#include <ast/identifier.hh>
#include <ast/type/named_type.hh>

#include <util/list.hh>
#include <util/utility.hh>

class Decl;
class ClassDecl;
class InterfaceDecl;
class VarDecl;
class FnDecl;

class Symbol_table {
public:
  void declare(Decl* declaration);
  void add_virtual(NamedType* interface_type, Decl* declaration);
  bool type_exists(std::string name);

  void check_virtual(Decl* declaration);
  void check_super(Decl* declaration);
  void set_super(Symbol_table& super_table) { super = &super_table; }
  void check_virtuals_implemented(ClassDecl* class_decl, List<NamedType*>* interface_types);
  void set_parent(Symbol_table& parent_table) { parent = &parent_table; }
  Decl* check_declared(Identifier* identifier);

  ClassDecl* get_class(std::string name);
  InterfaceDecl* get_interface(std::string name);
  void set_return_type(Type* type) { return_type = type; }
  void set_this_type(Type* type) { this_type = type; }
  Type* find_return_type();
  Type* find_this_type();
  bool class_extends_type(Type* subclass, Type* extends);

private:
  Declaration_table<ClassDecl> classes;
  Declaration_table<InterfaceDecl> interfaces;
  Declaration_table<VarDecl> variables;
  Declaration_table<FnDecl> functions;
  Virtual_table virtuals;
  Type* return_type = nullptr;
  Type* this_type = nullptr;

  Symbol_table* super = nullptr;
  Symbol_table* parent = nullptr;

  void detect_previous_declaration(Decl* new_declaration);
  FnDecl* find_inherited_function(std::string name);
  VarDecl* find_inherited_variable(std::string name);
};

#endif // SYMBOL_TABLE_H
