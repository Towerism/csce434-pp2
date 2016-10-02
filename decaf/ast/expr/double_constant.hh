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
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::doubleType; }
};

#endif /* DOUBLE_CONSTANT_H */
