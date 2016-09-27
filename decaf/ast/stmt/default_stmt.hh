#ifndef DEFAULT_STMT_H
#define DEFAULT_STMT_H

#include "stmt.hh"

#include <util/list.hh>

class DefaultStmt : public Stmt {
protected:
  List<Stmt*>* body;
public:
  DefaultStmt(yyltype loc, List<Stmt*>* body);
  const char *GetPrintNameForNode() { return "DefaultStmt";}
  void PrintChildren(int identLevel);
  void build_table() override;
  void analyze(reasonT focus) override;
};

#endif /* DEFAULT_STMT_H */
