#ifndef CASE_STMT_H
#define CASE_STMT_H

#include "stmt.hh"

#include <ast/expr/ast_expr.hh>

class CaseStmt : public Stmt {
protected:
  IntConstant* label;
  List<Stmt*>* body;
public:
  CaseStmt(yyltype loc, IntConstant* label, List<Stmt*>* body);
  const char *GetPrintNameForNode() { return "CaseStmt";}
  void PrintChildren(int identLevel);
  void build_table() override;
  void analyze(reasonT focus) override;
};

#endif /* CASE_STMT_H */
