#ifndef STMT_BLOCK_H
#define STMT_BLOCK_H

#include "stmt.hh"

#include <ast/symbol_table.hh>
#include <ast/decl/var_decl.hh>

#include <util/list.hh>

class StmtBlock : public Stmt {
protected:
  List<VarDecl*> *decls;
  List<Stmt*> *stmts;
  Symbol_table symbol_table;
public:
  StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
  const char *GetPrintNameForNode() override { return "StmtBlock"; }
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(reasonT focus) override;
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;
  void set_parent(Symbol_table& other) override;
};

#endif /* STMT_BLOCK_H */
