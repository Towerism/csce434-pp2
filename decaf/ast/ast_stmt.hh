/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. *
 * pp2: You will need to add new expression and statement node c
 * classes for the additional grammar elements (Switch/Postfix)
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include <util/list.hh>
#include "analyzable.hh"
#include "ast.hh"
#include "closeable.hh"
#include "scope_stack.hh"
#include "symbol_table.hh"

class Decl;
class VarDecl;
class Expr;
class IntConstant;

class Program : public Node, public Closeable
{
protected:
  List<Decl*> *decls;
public:
  Program(List<Decl*> *declList);
  const char *GetPrintNameForNode() { return "Program"; }
  void PrintChildren(int indentLevel);
  void build_table() override;
  void analyze(Scope_stack& scope_stack) override;

  static Symbol_table symbol_table;
};

class Stmt : public Node, public Closeable
{
public:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
  virtual void build_table() override {}
};

class StmtBlock : public Stmt {
protected:
  List<VarDecl*> *decls;
  List<Stmt*> *stmts;
  Symbol_table symbol_table;
public:
  StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
  const char *GetPrintNameForNode() { return "StmtBlock"; }
  void PrintChildren(int indentLevel);
  void build_table() override;
  void analyze(Scope_stack& scope_stack) override;
};

class ConditionalStmt : public Stmt
{
protected:
  Expr *test;
  Stmt *body;
  Symbol_table symbol_table;
public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
  virtual void build_table() override;
  virtual void analyze(Scope_stack& scope_stack) override;
};

class LoopStmt : public ConditionalStmt{
public:
  LoopStmt(Expr *testExpr, Stmt *body)
    : ConditionalStmt(testExpr, body) {}
};

class ForStmt : public LoopStmt{
protected:
  Expr *init, *step;
public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  const char *GetPrintNameForNode() { return "ForStmt"; }
  void PrintChildren(int indentLevel);
};

class WhileStmt : public LoopStmt{
public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  const char *GetPrintNameForNode() { return "WhileStmt"; }
  void PrintChildren(int indentLevel);
};

class IfStmt : public ConditionalStmt{
protected:
  Stmt *elseBody;
public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  const char *GetPrintNameForNode() { return "IfStmt"; }
  void PrintChildren(int indentLevel);
  void build_table() override;
  void analyze(Scope_stack& scope_stack) override;
};

class BreakStmt : public Stmt{
public:
  BreakStmt(yyltype loc) : Stmt(loc) {}
  const char *GetPrintNameForNode() { return "BreakStmt"; }
};

class CaseStmt : public Stmt {
protected:
  IntConstant* label;
  List<Stmt*>* body;
public:
  CaseStmt(yyltype loc, IntConstant* label, List<Stmt*>* body);
  const char *GetPrintNameForNode() { return "CaseStmt";}
  void PrintChildren(int identLevel);
  void build_table() override;
  void analyze(Scope_stack& scope_stack) override;
};

class DefaultStmt : public Stmt {
protected:
  List<Stmt*>* body;
public:
  DefaultStmt(yyltype loc, List<Stmt*>* body);
  const char *GetPrintNameForNode() { return "DefaultStmt";}
  void PrintChildren(int identLevel);
  void build_table() override;
  void analyze(Scope_stack& scope_stack) override;
};

class SwitchStmt : public Stmt {
protected:
  Expr* test;
  List<CaseStmt*>* cases;
  DefaultStmt* defaultStmt;
public:
  SwitchStmt(yyltype loc, Expr *test, List<CaseStmt*>* cases, DefaultStmt* defaultStmt);
  const char *GetPrintNameForNode() { return "SwitchStmt"; }
  void PrintChildren(int identLevel);
  void build_table() override;
  void analyze(Scope_stack& scope_stack) override;
};

class ReturnStmt : public Stmt{
protected:
  Expr *expr;
public:
  ReturnStmt(yyltype loc, Expr *expr);
  const char *GetPrintNameForNode() { return "ReturnStmt"; }
  void PrintChildren(int indentLevel);
};

class PrintStmt : public Stmt
{
protected:
  List<Expr*> *args;
public:
  PrintStmt(List<Expr*> *arguments);
  const char *GetPrintNameForNode() { return "PrintStmt"; }
  void PrintChildren(int indentLevel);
};


#endif
