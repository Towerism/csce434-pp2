#ifndef ARRAY_ACCESS_H
#define ARRAY_ACCESS_H

#include "lvalue.hh"

class ArrayAccess : public LValue {
protected:
  Expr *base, *subscript;
public:
  ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
  const char *GetPrintNameForNode() { return "ArrayAccess"; }
  void PrintChildren(int indentLevel);
};

#endif /* ARRAY_ACCESS_H */
