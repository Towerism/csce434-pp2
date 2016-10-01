#ifndef INT_CONSTANT_H
#define INT_CONSTANT_H

#include "expr.hh"

class IntConstant : public Expr {
protected:
  int value;
public:
  IntConstant(yyltype loc, int val);
  const char *GetPrintNameForNode() override { return "IntConstant"; }
  void PrintChildren(int indentLevel) override;
};

#endif /* INT_CONSTANT_H */
