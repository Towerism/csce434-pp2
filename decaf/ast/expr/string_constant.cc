#include "string_constant.hh"

#include <cstring>

#include <codegen/codegen.hh>
#include <util/utility.hh>

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
  Assert(val != NULL);
  value = strdup(val);
}

void StringConstant::PrintChildren(int indentLevel) {
  printf("%s",value);
}

void StringConstant::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  frame_location = codegen->GenLoadConstant(value, frame_allocator);
}
