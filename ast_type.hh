/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.
 */

#ifndef _H_ast_type
#define _H_ast_type

#include "ast.hh"
#include "list.hh"
#include "ast_stmt.hh"
#include "errors.hh"

class Type : public Node
{
 protected:
  char *typeName;

 public :
  static Type *intType, *doubleType, *boolType, *voidType,
    *nullType, *stringType, *errorType;

 Type(yyltype loc) : Node(loc) {}
  Type(const char *str);

  const char *GetPrintNameForNode() { return "Type"; }
  void PrintChildren(int indentLevel);
};

class NamedType : public Type
{
 protected:
  Identifier *id;

 public:
  NamedType(Identifier *i);

  const char *GetPrintNameForNode() { return "NamedType"; }
  void PrintChildren(int indentLevel);
  void analyze(Scope_stack& scope_stack) override;
  void analyze(Scope_stack& scope_stack, reasonT focus) override;
};

class ArrayType : public Type
{
 protected:
  Type *elemType;

 public:
  ArrayType(yyltype loc, Type *elemType);

  const char *GetPrintNameForNode() { return "ArrayType"; }
  void PrintChildren(int indentLevel);
  void analyze(Scope_stack& scope_stack) override;
  void analyze(Scope_stack& scope_stack, reasonT focus) override;
};


#endif
