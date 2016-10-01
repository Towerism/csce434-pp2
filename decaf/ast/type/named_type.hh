#ifndef NAMED_TYPE_H
#define NAMED_TYPE_H

#include "type.hh"
#include <ast/identifier.hh>

class NamedType : public Type
{
protected:
  Identifier *id;

public:
  NamedType(Identifier *i);

  const char *GetPrintNameForNode() override { return "NamedType"; }
  void PrintChildren(int indentLevel) override;
  void analyze(reasonT focus = LookingForType) override;

  std::string getName() override { return id->getName(); }
  bool equal(Type* other) override {
    auto* otherNamedType = dynamic_cast<NamedType*>(other);
    if (!otherNamedType)
      return false;
    return id->getName() == otherNamedType->id->getName();
  }
};

#endif /* NAMED_TYPE_H */
