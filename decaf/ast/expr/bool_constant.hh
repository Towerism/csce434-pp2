#ifndef BOOL_CONSTANT_H
#define BOOL_CONSTANT_H

#include "expr.hh"

class BoolConstant : public Expr {
protected:
  bool value;
public:
  BoolConstant(yyltype loc, bool val);
  const char *GetPrintNameForNode() override { return "BoolConstant"; }
  void PrintChildren(int indentLevel) override;
  Type* evaluate_type(Symbol_table* symbol_table) override { return Type::boolType; }
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
};

#endif /* BOOL_CONSTANT_H */
