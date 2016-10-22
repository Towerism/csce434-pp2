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
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
};

#endif /* STRING_CONSTANT_H */
