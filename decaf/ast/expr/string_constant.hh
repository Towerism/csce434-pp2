#ifndef STRING_CONSTANT_H
#define STRING_CONSTANT_H

#include "expr.hh"

class StringConstant : public Expr {
protected:
  char *value;
public:
  StringConstant(yyltype loc, const char *val);
  const char *GetPrintNameForNode() override { return "StringConstant"; }
  void PrintChildren(int indentLevel) override;
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::stringType; }
};

#endif /* STRING_CONSTANT_H */
