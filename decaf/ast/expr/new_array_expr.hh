#include "expr.hh"

#include <ast/type/type.hh>

class NewArrayExpr : public Expr {
protected:
  Expr *size;
  Type *elemType;

public:
  NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
  const char *GetPrintNameForNode() override { return "NewArrayExpr"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table *symbol_table, reasonT focus) override;
  Type *evaluate_type(Symbol_table *symbol_table) override;
  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                    Symbol_table *symbol_table) override;
private:
  Location* size_location;
  Location* size_needed_in_bytes;

  void emit_size_check(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                       Symbol_table *symbol_table);
  void emit_size_calculation(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                       Symbol_table *symbol_table);
  void emit_allocation(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                             Symbol_table *symbol_table);
};
