#ifndef THIS_H
#define THIS_H

#include "expr.hh"

class This : public Expr {
public:
  This(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() override { return "This"; }
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  Type* evaluate_type(Symbol_table* symbol_table) override;
  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;
};

#endif /* THIS_H */
