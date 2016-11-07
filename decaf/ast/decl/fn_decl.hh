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
  bool matches_prototype(FnDecl *other);

  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;
  void set_parent(Symbol_table &other) override;
  Type *get_type() override { return returnType; }
  List<VarDecl *> *get_formals() { return formals; }

  const char* get_label();
  void set_label_override(const char* value) { label_override = strdup(value); }
  void set_is_method() { is_method = true; }
  bool get_is_method() { return is_method; }

private:
  char* label_override = nullptr;
  bool is_method = false;
};

#endif /* FN_DECL_H */
