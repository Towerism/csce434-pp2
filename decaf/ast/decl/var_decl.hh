#ifndef VAR_DECL_H
#define VAR_DECL_H

#include <ast/decl/decl.hh>
#include <ast/type/ast_type.hh>

class VarDecl : public Decl
{
protected:
  Type *type;

public:
  VarDecl(Identifier *name, Type *type);
  const char *GetPrintNameForNode() { return "VarDecl"; }
  void PrintChildren(int indentLevel);
  void analyze(reasonT focus) override;

  Type* getType() { return type; }
};

#endif /* VAR_DECL_H */
