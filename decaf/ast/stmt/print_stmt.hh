#ifndef PRINT_STMT_H
#define PRINT_STMT_H

#include "stmt.hh"

#include <ast/expr/ast_expr.hh>

#include <codegen/codegen.hh>

class PrintStmt : public Stmt
{
protected:
  List<Expr*> *args;
public:
  PrintStmt(List<Expr*> *arguments);
  const char *GetPrintNameForNode() override { return "PrintStmt"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table* symbol_table, reasonT focus) override;
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;

private:
  void emit_print_arg(Expr* arg, CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table);

  BuiltIn built_in_from_type(Type* type);
};

#endif /* PRINT_STMT_H */
