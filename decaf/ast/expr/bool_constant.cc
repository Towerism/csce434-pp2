#include "bool_constant.hh"

#include <codegen/codegen.hh>

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
  value = val;
}

void BoolConstant::PrintChildren(int indentLevel) {
  printf("%s", value ? "true" : "false");
}

void BoolConstant::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  frame_location = codegen->GenLoadConstant(value, frame_allocator);
}
