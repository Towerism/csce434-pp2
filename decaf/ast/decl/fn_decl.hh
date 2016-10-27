#ifndef FN_DECL_H
#define FN_DECL_H

#include <ast/closeable.hh>
#include <ast/decl/ast_decl.hh>
#include <ast/decl/decl.hh>
#include <ast/identifier.hh>
#include <ast/node.hh>
#include <ast/stmt/ast_stmt.hh>
#include <ast/symbol_table.hh>
#include <ast/type/ast_type.hh>
#include <util/list.hh>

class FnDecl : public Decl {
protected:
  List<VarDecl *> *formals;
  Type *returnType;
  Stmt *body;
  Symbol_table symbol_table;
  Symbol_table formals_table;
  Expr *returnExpr;

public:
  FnDecl(Identifier *name, Type *returnType, List<VarDecl *> *formals);
  bool hasReturn() { return !returnType->equal(Type::voidType); }
  void SetFunctionBody(Stmt *b);
  const char *GetPrintNameForNode() override { return "FnDecl"; }
  void PrintChildren(int indentLevel) override;
  bool return_now(CodeGenerator *codegen,
                  Frame_allocator *frame_allocator,
                  Symbol_table *symbol_table,
                  Expr *expr) override;
  Expr *get_return_expr() { return returnExpr; }
  void build_table() override;
  void analyze(reasonT focus) override;
  bool matches_signature(FnDecl *other);

  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;
  void set_parent(Symbol_table &other) override;
  Type *get_type() override { return returnType; }
  List<VarDecl *> *get_formals() { return formals; }
};

#endif /* FN_DECL_H */
