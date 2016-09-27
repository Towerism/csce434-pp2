#ifndef LVALUE_H
#define LVALUE_H

#include "expr.hh"

class LValue : public Expr {
public:
  LValue(yyltype loc) : Expr(loc) {}
};

#endif /* LVALUE_H */
