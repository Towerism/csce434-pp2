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
  void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override;

  Type* getType() { return type; }
  Type* get_type() override { return type; }

  bool get_is_field() { return is_field; }
  void set_is_field() { is_field = true; }

private:
  bool is_field;
};

#endif /* VAR_DECL_H */
