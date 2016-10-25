class CodeGenerator;
class Frame_allocator;

#include <arch/tac.hh>

class Complex_op_factory {
public:
  Complex_op_factory(CodeGenerator* codegen, Frame_allocator* frame_allocator)
    : codegen(codegen), frame_allocator(frame_allocator), native_op(nullptr) {}

  Location* make_complex_op(const char* opName, Location* op1, Location* op2);

private:
  CodeGenerator* codegen;
  const char* opName;
  Location* op1;
  Location* op2;
  Frame_allocator* frame_allocator;

  Location* native_op;
  BinaryOp::OpCode native_op_code;

  void set_ops(const char* opName, Location* op1, Location* op2);
  bool op_is_atleast_semi_native();

  Location* process_semi_native_op();
  void set_native_op();
  void set_native_op_code();
  bool native_op_should_be_negated();
  Location* negate_native_op();
  Location* process_quasi_native_op();
};
