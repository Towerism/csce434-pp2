#ifndef CALL_H
#define CALL_H

#include "expr.hh"

#include <ast/identifier.hh>

#include <util/list.hh>
#include <util/utility.hh>

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */
class Call : public Expr {
protected:
  Expr *base; // will be NULL if no explicit base
  Identifier *field;
  List<Expr *> *actuals;

public:
  Call(yyltype loc, Expr *base, Identifier *field, List<Expr *> *args);
  const char *GetPrintNameForNode() override { return "Call"; }
  void PrintChildren(int indentLevel) override;
  void analyze(Symbol_table *symbol_table, reasonT focus) override;
  Type *evaluate_type(Symbol_table *symbol_table) override;
  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;

private:
  List<Type *> arg_types;
  Type *base_type;
  Symbol_table *calling_table = nullptr;
  Symbol_table *base_table = nullptr;

  void initialize_arg_types();
  void call_on_base();
  bool call_is_to_primitive_or_array_length();
  bool call_is_to_array();
  void check_function_declared_in_calling_table();
  bool args_length_is_good(Symbol_table *table_for_function);
  void check_args_types(Symbol_table *table_for_function);
  void call_on_scope();
  void check_args_length_and_types();
};

#endif /* CALL_H */
