#ifndef IF_STMT_H
#define IF_STMT_H

#include "conditional_stmt.hh"

class IfStmt : public ConditionalStmt{
protected:
  Stmt *elseBody;
public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  const char *GetPrintNameForNode() override { return "IfStmt"; }
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void set_parent(Symbol_table& other) override;
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
private:
  char* after_stmt_label;
  char* else_body_label;
  char* false_label;
  Location* test_location;

  void generate_labels(CodeGenerator* codegen);
  void generate_test_jump(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
  void generate_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
  void generate_else(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
};

#endif /* IF_STMT_H */
