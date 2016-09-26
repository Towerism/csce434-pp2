/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.
 */

#ifndef _H_ast_type
#define _H_ast_type

#include <string.h>
#include <string>

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
  virtual bool equal(Type* other) { return strcmp(typeName, other->typeName) == 0; }
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

  std::string getName() { return id->getName(); }
  bool equal(Type* other) {
    auto* otherNamedType = dynamic_cast<NamedType*>(other);
    if (!otherNamedType)
      return false;
    return id->getName() == otherNamedType->id->getName();
  }
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
  bool equal(Type* other) override {
    auto otherArrayType = dynamic_cast<ArrayType*>(other);
    if (!otherArrayType)
      return false;
    return elemType->equal(otherArrayType->elemType);
  }
};


#endif
