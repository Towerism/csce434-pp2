#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#include "type.hh"

class ArrayType : public Type
{
protected:
  Type *elemType;

public:
  ArrayType(yyltype loc, Type *elemType);

  const char *GetPrintNameForNode() override { return "ArrayType"; }
  void PrintChildren(int indentLevel) override;
  void analyze(reasonT focus) override;
  Type* get_elem_type() override { return elemType; }
  void verify(reasonT focus) override;
  bool equal(Type* other) override {
    if (other == Type::errorType
        || this == Type::errorType
        || other == Type::nullType
        || this == Type::nullType)
      return true;
    auto otherArrayType = dynamic_cast<ArrayType*>(other);
    if (!otherArrayType)
      return false;
    return elemType->equal(otherArrayType->elemType);
  }
  std::string getName() override { return elemType->getName() + "[]"; }
};

#endif /* ARRAY_TYPE_H */
