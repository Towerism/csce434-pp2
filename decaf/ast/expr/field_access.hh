#include "lvalue.hh"

#include "expr.hh"

#include <ast/identifier.hh>

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
class FieldAccess : public LValue {
protected:
  Expr *base;	// will be NULL if no explicit base
  Identifier *field;
public:
  FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
  const char *GetPrintNameForNode() override { return "FieldAccess"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
};
