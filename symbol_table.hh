#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>

class Decl;
class ClassDecl;

class Symbol_table {
public:
  void declare(Decl* declaration);
  void declare_class(ClassDecl* class_declaration);
  ClassDecl* class_exists(std::string name);

private:
  std::unordered_map<std::string, ClassDecl*> class_declarations;
};

#endif // SYMBOL_TABLE_H
