#ifndef STMT_H
#define STMT_H

#include <ast/node.hh>
#include <ast/closeable.hh>
#include <ast/emittable.hh>

class Stmt : public Node, public Closeable, public Emittable
{
public:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
  virtual void build_table() override {}
  virtual void set_parent(Symbol_table& other) override {}
  virtual void emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) override {}
};

#endif /* STMT_H */
