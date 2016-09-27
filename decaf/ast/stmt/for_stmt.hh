#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "loop_stmt.hh"

class ForStmt : public LoopStmt{
protected:
  Expr *init, *step;
public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  const char *GetPrintNameForNode() { return "ForStmt"; }
  void PrintChildren(int indentLevel);
};

#endif /* FOR_STMT_H */
