#include "int_constant.hh"

#include <codegen/codegen.hh>

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
  value = val;
}

void IntConstant::PrintChildren(int indentLevel) {
  printf("%d", value);
}

void IntConstant::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  frame_location = codegen->GenLoadConstant(value, frame_allocator);
}
