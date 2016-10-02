#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <iostream>

#include "node.hh"

class Identifier : public Node
{
protected:
  char *name;

public:
  Identifier(yyltype loc, const char *name);
  const char *GetPrintNameForNode() override { return "Identifier"; }
  void PrintChildren(int indentLevel) override;
  std::string getName() const { return std::string(name); }

  friend std::ostream& operator<<(std::ostream& out, Identifier* id) {
    return out << id->name;
  }
};

#endif /* IDENTIFIER_H */
