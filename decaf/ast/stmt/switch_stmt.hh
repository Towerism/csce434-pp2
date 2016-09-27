#ifndef SWITCH_STMT_H
#define SWITCH_STMT_H

#include "stmt.hh"
#include "case_stmt.hh"
#include "default_stmt.hh"

#include <util/list.hh>

class SwitchStmt : public Stmt {
protected:
  Expr* test;
  List<CaseStmt*>* cases;
  DefaultStmt* defaultStmt;
public:
  SwitchStmt(yyltype loc, Expr *test, List<CaseStmt*>* cases, DefaultStmt* defaultStmt);
  const char *GetPrintNameForNode() { return "SwitchStmt"; }
  void PrintChildren(int identLevel);
  void build_table() override;
  void analyze(reasonT focus) override;
};

#endif /* SWITCH_STMT_H */
