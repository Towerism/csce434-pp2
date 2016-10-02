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
  const char *GetPrintNameForNode() override { return "VarDecl"; }
  void PrintChildren(int indentLevel) override;
  void analyze(reasonT focus) override;

  Type* getType() { return type; }
  Type* get_type() override { return type; }
};

#endif /* VAR_DECL_H */
