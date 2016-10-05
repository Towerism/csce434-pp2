#ifndef EMPTY_EXPR_H
#define EMPTY_EXPR_H

#include "expr.hh"

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr {
public:
  const char *GetPrintNameForNode() override { return "Empty"; }
  yyltype* get_location_or_default(yyltype* loc) override { return loc; }
};

#endif /* EMPTY_EXPR_H */
