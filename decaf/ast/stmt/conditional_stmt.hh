#ifndef CONDITIONAL_STMT_H
#define CONDITIONAL_STMT_H

#include "stmt.hh"

#include <ast/symbol_table.hh>
#include <ast/expr/ast_expr.hh>

#include <iostream>
class ConditionalStmt : public Stmt
{
protected:
  Expr *test;
  Stmt *body;
  Symbol_table symbol_table;

  bool exit_stmt_after_body = false;
  char* before_stmt_label;
  char* after_stmt_label;
  char* false_label;
  Location* test_location;

  virtual void generate_before_stmt_end(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {}
  virtual void generate_extra_labels(CodeGenerator* codegen) {}
  virtual void generate_after_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {}
public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
  virtual void build_table() override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void set_parent(Symbol_table& other) override { body->set_parent(other); }
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
private:
  void generate_labels(CodeGenerator* codegen);
  void generate_test_jump(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
  void generate_body(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);
};


#endif /* CONDITIONAL_STMT_H */
