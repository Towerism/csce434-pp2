#include "expr.hh"

#include <ast/type/type.hh>

class NewArrayExpr : public Expr {
protected:
  Expr *size;
  Type *elemType;
public:
  NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
  const char *GetPrintNameForNode() { return "NewArrayExpr"; }
  void PrintChildren(int indentLevel);
};
