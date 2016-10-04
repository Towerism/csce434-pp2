#ifndef READ_LINE_EXPR_H
#define READ_LINE_EXPR_H

#include "expr.hh"

class ReadLineExpr : public Expr {
public:
  ReadLineExpr(yyltype loc) : Expr (loc) {}
  const char *GetPrintNameForNode() override { return "ReadLineExpr"; }
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::stringType; }
};

#endif /* READ_LINE_EXPR_H */
