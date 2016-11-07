#include "null_constant.hh"

#include <codegen/codegen.hh>

void NullConstant::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                        Symbol_table *symbol_table) {
  frame_location = codegen->GenLoadConstant(0, frame_allocator);
}
