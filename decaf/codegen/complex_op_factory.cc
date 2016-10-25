#include "complex_op_factory.hh"

#include "codegen.hh"

#include <arch/tac.hh>

#include <cstring>

Location* Complex_op_factory::make_complex_op(const char* opName, Location* op1, Location* op2) {
  if (op_is_atleast_semi_native(opName)) {
    Location* semi_native_op = process_semi_native_op(opName, op1, op2);
    if (semi_native_op)
      return semi_native_op;
  } else
    return process_quasi_native_op(opName, op1, op2);

  Location *result = codegen->GenNot(native_op, frame_allocator);

  return result;
}

bool Complex_op_factory::op_is_atleast_semi_native(const char* opName) {
  return strcmp(opName, "==") == 0 || strcmp(opName, "!=") == 0 || strcmp(opName, "<") == 0 || strcmp(opName, ">=") == 0;
}

Location* Complex_op_factory::process_semi_native_op(const char* opName, Location* op1, Location* op2) {
  if (strcmp(opName, "==") == 0 || strcmp(opName, "!=") == 0) {
    native_op = codegen->GenBinaryOp(BinaryOp::Eq, op1, op2, frame_allocator);
    if (strcmp(opName, "==") == 0)
      return native_op;
  } else { // (strcmp(opName, "<") == 0 || strcmp(opName, ">=") == 0)
    native_op = codegen->GenBinaryOp(BinaryOp::Less, op1, op2, frame_allocator);
    if (strcmp(opName, "<") == 0)
      return native_op;
  }
  return nullptr;
}

Location* Complex_op_factory::process_quasi_native_op(const char* opName, Location* op1, Location* op2) {
  if (strcmp(opName, ">") == 0)
    return make_complex_op("<", op2, op1);
  else // (strcmp(opName, "<=") == 0)
    return make_complex_op(">=", op2, op1);
}
