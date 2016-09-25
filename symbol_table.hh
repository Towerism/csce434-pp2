#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>

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
  std::unordered_map<std::string, ClassDecl*> class_declarations;
  std::unordered_map<std::string, InterfaceDecl*> interface_declarations;
  std::unordered_map<std::string, VarDecl*> variable_declarations;

  ClassDecl* class_exists(std::string name);
  InterfaceDecl* interface_exists(std::string name);
  VarDecl* variable_exists(std::string name);
};

#endif // SYMBOL_TABLE_H
