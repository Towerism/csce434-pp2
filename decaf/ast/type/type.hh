#ifndef TYPE_H
#define TYPE_H

#include <ast/node.hh>
#include <string.h>

class Type : public Node
{
protected:
  char *typeName;

public :
  static Type *intType, *doubleType, *boolType, *voidType,
    *nullType, *stringType, *errorType;

  Type() {}
  Type(yyltype loc) : Node(loc) {}
  Type(const char *str);

  const char *GetPrintNameForNode() override { return "Type"; }
  void PrintChildren(int indentLevel) override;
  virtual bool equal(Type* other);
  virtual bool coerce(Type* other, Symbol_table* symbol_table) { return equal(other); }
  virtual std::string getName() { return std::string(typeName); }

  friend std::ostream& operator<<(std::ostream& out, Type* type) {
    return out << type->getName();
  }
};

#endif /* TYPE_H */
