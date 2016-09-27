#ifndef FN_DECL_H
#define FN_DECL_H

#include <util/list.hh>
#include <ast/node.hh>
#include <ast/identifier.hh>
#include <ast/closeable.hh>
#include <ast/symbol_table.hh>
#include <ast/decl/decl.hh>
#include <ast/decl/ast_decl.hh>
#include <ast/stmt/ast_stmt.hh>
#include <ast/type/ast_type.hh>

class FnDecl : public Decl
{
protected:
  List<VarDecl*> *formals;
  Type *returnType;
  Stmt *body;
  Symbol_table symbol_table;

public:
  FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
  void SetFunctionBody(Stmt *b);
  const char *GetPrintNameForNode() { return "FnDecl"; }
  void PrintChildren(int indentLevel);
  void build_table() override;
  void analyze(reasonT focus) override;
  bool matches_signature(FnDecl* other);
};

#endif /* FN_DECL_H */
