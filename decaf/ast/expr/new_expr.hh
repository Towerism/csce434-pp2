#include "expr.hh"

#include <ast/type/named_type.hh>

class NewExpr : public Expr {
protected:
  NamedType *cType;
public:
  NewExpr(yyltype loc, NamedType *clsType);
  const char *GetPrintNameForNode() { return "NewExpr"; }
  void PrintChildren(int indentLevel);
};
