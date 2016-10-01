#ifndef WHILE_STMT_H
#define WHILE_STMT_H

#include "loop_stmt.hh"

class WhileStmt : public LoopStmt{
public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  const char *GetPrintNameForNode() override { return "WhileStmt"; }
  void PrintChildren(int indentLevel) override;
};

#endif /* WHILE_STMT_H */
