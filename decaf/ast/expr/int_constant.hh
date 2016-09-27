#ifndef INT_CONSTANT_H
#define INT_CONSTANT_H

#include "expr.hh"

class IntConstant : public Expr {
protected:
  int value;
public:
  IntConstant(yyltype loc, int val);
  const char *GetPrintNameForNode() { return "IntConstant"; }
  void PrintChildren(int indentLevel);
};

#endif /* INT_CONSTANT_H */
