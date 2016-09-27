#ifndef PROGRAM_H
#define PROGRAM_H

#include <ast/node.hh>
#include <ast/closeable.hh>
#include <ast/symbol_table.hh>
#include <ast/decl/decl.hh>

#include <util/errors.hh>
#include <util/list.hh>

class Program : public Node, public Closeable
{
protected:
  List<Decl*> *decls;
public:
  Program(List<Decl*> *declList);
  const char *GetPrintNameForNode() { return "Program"; }
  void PrintChildren(int indentLevel);
  void build_table() override;
  void analyze(reasonT focus = LookingForType) override;

  static Symbol_table symbol_table;
};

#endif /* PROGRAM_H */
