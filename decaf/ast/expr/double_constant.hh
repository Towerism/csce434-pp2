#ifndef DOUBLE_CONSTANT_H
#define DOUBLE_CONSTANT_H

#include "expr.hh"

class DoubleConstant : public Expr {
protected:
  double value;
public:
  DoubleConstant(yyltype loc, double val);
  const char *GetPrintNameForNode() override { return "DoubleConstant"; }
  void PrintChildren(int indentLevel) override;
};

#endif /* DOUBLE_CONSTANT_H */
