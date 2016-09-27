#ifndef STRING_CONSTANT_H
#define STRING_CONSTANT_H

#include "expr.hh"

class StringConstant : public Expr {
protected:
  char *value;
public:
  StringConstant(yyltype loc, const char *val);
  const char *GetPrintNameForNode() { return "StringConstant"; }
  void PrintChildren(int indentLevel);
};

#endif /* STRING_CONSTANT_H */
