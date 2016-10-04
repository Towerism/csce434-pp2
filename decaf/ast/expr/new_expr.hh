#include "expr.hh"

#include <ast/type/named_type.hh>

class NewExpr : public Expr {
protected:
  NamedType *cType;

public:
  NewExpr(yyltype loc, NamedType *clsType);
  const char *GetPrintNameForNode() override { return "NewExpr"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  Type* evaluate_type(Symbol_table* symbol_table) override { return cType; }
};
