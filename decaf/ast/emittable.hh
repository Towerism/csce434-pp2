#ifndef EMITTABLE_H
#define EMITTABLE_H

class CodeGenerator;
class Frame_allocator;
class Symbol_table;

class Emittable {
public:
  virtual void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) = 0;
  virtual ~Emittable() = default;
};

#endif /* EMITTABLE_H */
