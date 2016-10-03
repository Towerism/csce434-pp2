#ifndef CALL_H
#define CALL_H

#include "expr.hh"

#include <ast/identifier.hh>

#include <util/list.hh>
#include <util/utility.hh>

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */
class Call : public Expr {
protected:
  Expr *base;	// will be NULL if no explicit base
  Identifier *field;
  List<Expr*> *actuals;
public:
  Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);
  const char *GetPrintNameForNode() override { return "Call"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  Type* evaluate_type(Symbol_table* symbol_table) override;
};

#endif /* CALL_H */
