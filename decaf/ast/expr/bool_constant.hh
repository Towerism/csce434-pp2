#ifndef BOOL_CONSTANT_H
#define BOOL_CONSTANT_H

#include "expr.hh"

class BoolConstant : public Expr {
protected:
  bool value;
public:
  BoolConstant(yyltype loc, bool val);
  const char *GetPrintNameForNode() { return "BoolConstant"; }
  void PrintChildren(int indentLevel);
};

#endif /* BOOL_CONSTANT_H */
