#ifndef COMPOUND_EXPR_H
#define COMPOUND_EXPR_H

#include "expr.hh"
#include "operator.hh"

class CompoundExpr : public Expr {
protected:
  Operator *op;
  Expr *left, *right; // left will be NULL if unary
public:
  CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
  CompoundExpr(Operator *op, Expr *rhs);             // for unary
  CompoundExpr(Expr *lhs, Operator *op);             // for postfix
  void PrintChildren(int indentLevel);
};

#endif /* COMPOUND_EXPR_H */
