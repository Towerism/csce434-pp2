#ifndef PRINT_STMT_H
#define PRINT_STMT_H

#include "stmt.hh"

#include <ast/expr/ast_expr.hh>

class PrintStmt : public Stmt
{
protected:
  List<Expr*> *args;
public:
  PrintStmt(List<Expr*> *arguments);
  const char *GetPrintNameForNode() { return "PrintStmt"; }
  void PrintChildren(int indentLevel);
};

#endif /* PRINT_STMT_H */
