#ifndef IF_STMT_H
#define IF_STMT_H

#include "conditional_stmt.hh"

class IfStmt : public ConditionalStmt{
protected:
  Stmt *elseBody;
public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  const char *GetPrintNameForNode() override { return "IfStmt"; }
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
};

#endif /* IF_STMT_H */
