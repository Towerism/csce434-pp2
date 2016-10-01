#ifndef BREAK_STMT_H
#define BREAK_STMT_H

#include "stmt.hh"

class BreakStmt : public Stmt{
public:
  BreakStmt(yyltype loc) : Stmt(loc) {}
  const char *GetPrintNameForNode() override { return "BreakStmt"; }
};

#endif /* BREAK_STMT_H */
