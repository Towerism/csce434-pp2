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
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::intType; }
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
};

#endif /* INT_CONSTANT_H */
