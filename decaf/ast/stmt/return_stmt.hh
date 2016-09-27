#ifndef RETURN_STMT_H
#define RETURN_STMT_H

#include "stmt.hh"

#include <ast/expr/ast_expr.hh>

class ReturnStmt : public Stmt{
protected:
  Expr *expr;
public:
  ReturnStmt(yyltype loc, Expr *expr);
  const char *GetPrintNameForNode() { return "ReturnStmt"; }
  void PrintChildren(int indentLevel);
};

#endif /* RETURN_STMT_H */
