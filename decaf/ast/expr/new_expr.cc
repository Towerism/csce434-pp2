#include "new_expr.hh"

#include <util/utility.hh>

#include <ast/identifier.hh>
#include <ast/stmt/program.hh>

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType = c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) { cType->Print(indentLevel + 1); }

void NewExpr::analyze(Symbol_table *symbol_table, reasonT focus) {
  cType->verify(LookingForClass);
}
