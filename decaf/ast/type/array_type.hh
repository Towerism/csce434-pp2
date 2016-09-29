#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#include "type.hh"

class ArrayType : public Type
{
protected:
  Type *elemType;

public:
  ArrayType(yyltype loc, Type *elemType);

  const char *GetPrintNameForNode() { return "ArrayType"; }
  void PrintChildren(int indentLevel);
  void analyze(reasonT focus) override;
  bool equal(Type* other) override {
    auto otherArrayType = dynamic_cast<ArrayType*>(other);
    if (!otherArrayType)
      return false;
    return elemType->equal(otherArrayType->elemType);
  }
  std::string getName() override { return elemType->getName(); }
};

#endif /* ARRAY_TYPE_H */
