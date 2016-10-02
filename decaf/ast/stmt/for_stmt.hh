#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "loop_stmt.hh"

class ForStmt : public LoopStmt{
protected:
  Expr *init, *step;
public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  const char *GetPrintNameForNode() override { return "ForStmt"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
};

#endif /* FOR_STMT_H */
