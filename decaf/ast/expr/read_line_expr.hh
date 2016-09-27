#ifndef READ_LINE_EXPR_H
#define READ_LINE_EXPR_H

#include "expr.hh"

class ReadLineExpr : public Expr {
public:
  ReadLineExpr(yyltype loc) : Expr (loc) {}
  const char *GetPrintNameForNode() { return "ReadLineExpr"; }
};

#endif /* READ_LINE_EXPR_H */
