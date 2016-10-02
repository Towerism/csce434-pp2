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
  Symbol_table formals_table;

public:
  FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
  void SetFunctionBody(Stmt *b);
  const char *GetPrintNameForNode() override { return "FnDecl"; }
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(reasonT focus) override;
  bool matches_signature(FnDecl* other);
  void set_parent(Symbol_table& other) override;
  Type* get_type() override { return returnType; }
};

#endif /* FN_DECL_H */
