#ifndef DEFAULT_STMT_H
#define DEFAULT_STMT_H

#include "stmt.hh"

#include <util/list.hh>

class DefaultStmt : public Stmt {
protected:
  List<Stmt*>* body;
public:
  DefaultStmt(yyltype loc, List<Stmt*>* body);
  const char *GetPrintNameForNode() override { return "DefaultStmt";}
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(reasonT focus) override;
  void set_parent(Symbol_table& other) override;
};

#endif /* DEFAULT_STMT_H */
