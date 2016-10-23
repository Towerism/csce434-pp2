#include "compound_expr.hh"

#include <util/utility.hh>

#include <ast/symbol_table.hh>
#include <codegen/codegen.hh>

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r)  : Expr(Join(l->GetLocation(), r->GetLocation())) {
  Assert(l != NULL && o != NULL && r != NULL);
  (op=o)->SetParent(this);
  (left=l)->SetParent(this);
  (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r)  : Expr(Join(o->GetLocation(), r->GetLocation())) {
  Assert(o != NULL && r != NULL);
  left = NULL;
  (op=o)->SetParent(this);
  (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o)  : Expr(Join(l->GetLocation(), o->GetLocation())) {
  Assert(l != NULL && o != NULL);
  right = NULL;
  (op=o)->SetParent(this);
  (left=l)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
  if (left) left->Print(indentLevel+1);
  op->Print(indentLevel+1);
  if (right) right->Print(indentLevel+1);
}

void CompoundExpr::analyze(Symbol_table* symbol_table, reasonT focus) {
  if (left)
    left->analyze(symbol_table, focus);
  if (right)
    right->analyze(symbol_table, focus);
}

bool CompoundExpr::left_is_compatible_with_right(Symbol_table* symbol_table) {
  Type* left_type = nullptr;
  auto right_type = right->evaluate_type(symbol_table);
  if (left)
    left_type = left->evaluate_type(symbol_table);
  else
    return right_type->equal(Type::intType) || right_type->equal(Type::doubleType);
  right_type = right->evaluate_type(symbol_table);
  return (left_type->equal(Type::intType) || left_type->equal(Type::doubleType))
    && left_type->equal(right_type);
}

void CompoundExpr::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  left->emit(codegen, frame_allocator, symbol_table);
  right->emit(codegen, frame_allocator, symbol_table);
}
