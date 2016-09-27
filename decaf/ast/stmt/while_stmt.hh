#ifndef WHILE_STMT_H
#define WHILE_STMT_H

#include "loop_stmt.hh"

class WhileStmt : public LoopStmt{
public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  const char *GetPrintNameForNode() { return "WhileStmt"; }
  void PrintChildren(int indentLevel);
};

#endif /* WHILE_STMT_H */
