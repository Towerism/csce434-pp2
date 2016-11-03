#ifndef ARRAY_ACCESS_H
#define ARRAY_ACCESS_H

#include "lvalue.hh"

class ArrayAccess : public LValue {
protected:
  Expr *base, *subscript;

public:
  ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
  const char *GetPrintNameForNode() override { return "ArrayAccess"; }
  void PrintChildren(int indentLevel) override;
  bool needs_dereference() override { return true; }
  void analyze(Symbol_table *symbol_table, reasonT focus) override;
  Type *evaluate_type(Symbol_table *symbol_table) override;
  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;

private:
  char *after_error_label;
  Location *base_location;
  Location *subscript_location;

  void calculate_locations(CodeGenerator *codegen,
                           Frame_allocator *frame_allocator,
                           Symbol_table *symbol_table);
  void emit_subscript_check(CodeGenerator *codegen,
                            Frame_allocator *frame_allocator,
                            Symbol_table *symbol_table);
  void emit_frame_location(CodeGenerator *codegen,
                           Frame_allocator *frame_allocator,
                           Symbol_table *symbol_table);
};

#endif /* ARRAY_ACCESS_H */
