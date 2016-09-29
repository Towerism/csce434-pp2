#ifndef INTERFACE_DECL_H
#define INTERFACE_DECL_H

#include <iostream>

#include <util/list.hh>
#include <ast/node.hh>
#include <ast/identifier.hh>
#include <ast/closeable.hh>
#include <ast/symbol_table.hh>
#include <ast/decl/decl.hh>

class InterfaceDecl : public Decl
{
protected:
  List<Decl*> *members;
  Symbol_table symbol_table;

public:
  InterfaceDecl(Identifier *name, List<Decl*> *members);
  const char *GetPrintNameForNode() { return "InterfaceDecl"; }
  void PrintChildren(int indentLevel);
  void build_table() override;

  List<Decl*>* get_members() { return members; }
};

#endif /* INTERFACE_DECL_H */
