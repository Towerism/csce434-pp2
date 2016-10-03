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
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  Type* evaluate_type(Symbol_table* symbol_table) override;
};
