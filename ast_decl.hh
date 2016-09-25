/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.hh"
#include "closeable.hh"
#include "list.hh"

class Type;
class NamedType;
class Identifier;
class Stmt;

class Decl : public Node, public Closeable
{
 protected:
  Identifier *id;

 public:
  Decl(Identifier *name);
  std::string getName() const { return id->getName(); }
  virtual void build_table() override {}

  friend std::ostream& operator<<(std::ostream& out, Decl* decl) {
    return out << decl->getName();
  }
};

class VarDecl : public Decl
{
 protected:
  Type *type;

 public:
  VarDecl(Identifier *name, Type *type);
  const char *GetPrintNameForNode() { return "VarDecl"; }
  void PrintChildren(int indentLevel);
  void analyze(Scope_stack& scope_stack) override;
};

class ClassDecl : public Decl
{
 protected:
  List<Decl*> *members;
  NamedType *extends;
  List<NamedType*> *implements;

 public:
  ClassDecl(Identifier *name, NamedType *extends,
            List<NamedType*> *implements, List<Decl*> *members);
  const char *GetPrintNameForNode() { return "ClassDecl"; }
  void PrintChildren(int indentLevel);
  void analyze(Scope_stack& scope_stack) override;
};

class InterfaceDecl : public Decl
{
 protected:
  List<Decl*> *members;

 public:
  InterfaceDecl(Identifier *name, List<Decl*> *members);
  const char *GetPrintNameForNode() { return "InterfaceDecl"; }
  void PrintChildren(int indentLevel);
  void analyze(Scope_stack& scope_stack) override;
};

class FnDecl : public Decl
{
 protected:
  List<VarDecl*> *formals;
  Type *returnType;
  Stmt *body;

 public:
  FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
  void SetFunctionBody(Stmt *b);
  const char *GetPrintNameForNode() { return "FnDecl"; }
  void PrintChildren(int indentLevel);
  void analyze(Scope_stack& scope_stack) override;
};

#endif
