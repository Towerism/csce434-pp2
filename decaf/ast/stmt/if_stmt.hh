#ifndef IF_STMT_H
#define IF_STMT_H

#include "conditional_stmt.hh"

class IfStmt : public ConditionalStmt{
protected:
  Stmt *elseBody;

  void generate_extra_labels(CodeGenerator* codegen) override;
  void generate_before_stmt_end(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
  void generate_after_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  const char *GetPrintNameForNode() override { return "IfStmt"; }
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void set_parent(Symbol_table& other) override;
private:
  char* else_body_label;

  void generate_labels(CodeGenerator* codegen);
  void generate_test_jump(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
  void generate_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
  void generate_else(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
};

#endif /* IF_STMT_H */
