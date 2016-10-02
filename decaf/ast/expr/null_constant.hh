#ifndef NULL_CONSTANT_H
#define NULL_CONSTANT_H

#include "expr.hh"

class NullConstant: public Expr {
public:    NullConstant(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() override { return "NullConstant"; }
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::nullType; }
};

#endif /* NULL_CONSTANT_H */
