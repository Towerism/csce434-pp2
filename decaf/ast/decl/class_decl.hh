#ifndef CLASS_DECL_H
#define CLASS_DECL_H

#include <ast/symbol_table.hh>
#include <ast/decl/decl.hh>
#include <ast/type/ast_type.hh>

#include <util/list.hh>

class ClassDecl : public Decl
{
protected:
  List<Decl*> *members;
  NamedType *extends;
  List<NamedType*> *implements;
  Symbol_table symbol_table;

public:
  ClassDecl(Identifier *name, NamedType *extends,
            List<NamedType*> *implements, List<Decl*> *members);
  const char *GetPrintNameForNode() { return "ClassDecl"; }
  void PrintChildren(int indentLevel);
  void build_table() override;
  void analyze(reasonT focus) override;

private:
  void add_virtuals();
  void extend();
};

#endif /* CLASS_DECL_H */