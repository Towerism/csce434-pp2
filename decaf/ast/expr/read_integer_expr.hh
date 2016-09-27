#ifndef READ_INTEGER_EXPR_H
#define READ_INTEGER_EXPR_H

#include "expr.hh"

class ReadIntegerExpr : public Expr {
public:
  ReadIntegerExpr(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() { return "ReadIntegerExpr"; }
};

#endif /* READ_INTEGER_EXPR_H */
