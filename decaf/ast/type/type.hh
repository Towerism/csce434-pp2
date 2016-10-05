#ifndef TYPE_H
#define TYPE_H

#include <ast/node.hh>
#include <string.h>
#include <vector>

class Type : public Node
{
protected:
  char *typeName;

public :
  static Type *intType, *doubleType, *boolType, *voidType,
    *nullType, *stringType, *errorType;
  static std::vector<Type*> primitives;

  Type() {}
  Type(yyltype loc) : Node(loc) {}
  Type(const char *str);

  const char *GetPrintNameForNode() override { return "Type"; }
  void PrintChildren(int indentLevel) override;
  virtual bool equal(Type* other);
  virtual bool coerce(Type* other, Symbol_table* symbol_table) { return equal(other); }
  virtual std::string getName() { return std::string(typeName); }
  virtual Type* get_elem_type() { return this; }
  virtual void verify(reasonT focus) {}
  bool is_primitive();

  friend std::ostream& operator<<(std::ostream& out, Type* type) {
    return out << type->getName();
  }
};

#endif /* TYPE_H */
