class CodeGenerator;
class Location;
class Frame_allocator;

class Complex_op_factory {
public:
  Complex_op_factory(CodeGenerator* codegen, Frame_allocator* frame_allocator)
    : codegen(codegen), frame_allocator(frame_allocator), native_op(nullptr) {}

  Location* make_complex_op(const char* opName, Location* op1, Location* op2);

private:
  CodeGenerator* codegen;
  char* opName;
  Location* op1;
  Location* op2;
  Frame_allocator* frame_allocator;

  Location* native_op;
  bool op_is_atleast_semi_native(const char* opName);

  Location* process_semi_native_op(const char* opName, Location* op1, Location* op2);
  Location* process_quasi_native_op(const char* opName, Location* op1, Location* op2);
};
