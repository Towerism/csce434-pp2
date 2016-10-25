#include "complex_op_factory.hh"

#include "codegen.hh"

#include <arch/tac.hh>

#include <cstring>

Location* Complex_op_factory::make_complex_op(const char* opName, Location* op1, Location* op2) {
  set_ops(opName, op1, op2);
  if (op_is_atleast_semi_native())
     return process_semi_native_op();
  else
    return process_quasi_native_op();
}

void Complex_op_factory::set_ops(const char* opName, Location* op1, Location* op2) {
  this->opName = opName;
  this->op1 = op1;
  this->op2 = op2;
}

bool Complex_op_factory::op_is_atleast_semi_native() {
  return strcmp(opName, "==") == 0 || strcmp(opName, "!=") == 0 || strcmp(opName, "<") == 0 || strcmp(opName, ">=") == 0;
}

Location* Complex_op_factory::process_semi_native_op() {
  set_native_op();
  if (native_op_should_be_negated())
    return negate_native_op();
  return native_op;
}

void Complex_op_factory::set_native_op() {
  set_native_op_code();
  native_op = codegen->GenBinaryOp(native_op_code, op1, op2, frame_allocator);
}

void Complex_op_factory::set_native_op_code() {
  if (strcmp(opName, "==") == 0 || strcmp(opName, "!=") == 0)
    native_op_code = BinaryOp::Eq;
  else // (strcmp(opName, "<") == 0 || strcmp(opName, ">=") == 0)
    native_op_code = BinaryOp::Less;
}

bool Complex_op_factory::native_op_should_be_negated() {
  return strcmp(opName, "==") != 0 && strcmp(opName, "<") != 0;
}

Location* Complex_op_factory::negate_native_op() {
  return codegen->GenNot(native_op, frame_allocator);
}

Location* Complex_op_factory::process_quasi_native_op() {
  if (strcmp(opName, ">") == 0)
    return make_complex_op("<", op2, op1);
  else // (strcmp(opName, "<=") == 0)
    return make_complex_op(">=", op2, op1);
}
