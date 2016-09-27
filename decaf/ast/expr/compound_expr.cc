#include "compound_expr.hh"

#include <util/utility.hh>

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r)  : Expr(Join(l->GetLocation(), r->GetLocation())) {
  Assert(l != NULL && o != NULL && r != NULL);
  (op=o)->SetParent(this);
  (left=l)->SetParent(this);
  (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r)  : Expr(Join(o->GetLocation(), r->GetLocation())) {
  Assert(o != NULL && r != NULL);
  left = NULL;
  (op=o)->SetParent(this);
  (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o)  : Expr(Join(l->GetLocation(), o->GetLocation())) {
  Assert(l != NULL && o != NULL);
  right = NULL;
  (op=o)->SetParent(this);
  (left=l)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
  if (left) left->Print(indentLevel+1);
  op->Print(indentLevel+1);
  if (right) right->Print(indentLevel+1);
}
