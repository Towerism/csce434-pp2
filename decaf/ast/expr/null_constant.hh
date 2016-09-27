#ifndef NULL_CONSTANT_H
#define NULL_CONSTANT_H

#include "expr.hh"

class NullConstant: public Expr {
public:    NullConstant(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() { return "NullConstant"; }
};

#endif /* NULL_CONSTANT_H */
