#ifndef THIS_H
#define THIS_H

#include "expr.hh"

class This : public Expr {
public:
  This(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() { return "This"; }
};

#endif /* THIS_H */
