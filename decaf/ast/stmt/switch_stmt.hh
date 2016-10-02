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
  const char *GetPrintNameForNode() override { return "SwitchStmt"; }
  void PrintChildren(int identLevel) override;
  void build_table() override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void set_parent(Symbol_table& other) override;
};

#endif /* SWITCH_STMT_H */
