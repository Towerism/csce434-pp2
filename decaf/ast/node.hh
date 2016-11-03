#ifndef NODE_H
#define NODE_H

#include <parse/location.hh>
#include <arch/tac.hh>
#include <util/errors.hh>

#include "analyzable.hh"

class CodeGenerator;
class Frame_allocator;

class Node : public Analyzable {
protected:
  yyltype *location;
  Node *parent;
  bool is_break_node = false;
  Location* reference = nullptr;
  Location* frame_location = nullptr;

public:
  Node(yyltype loc);
  Node();

  yyltype *GetLocation() { return location; }
  void SetParent(Node *p) { parent = p; }
  Node *GetParent() { return parent; }

  virtual const char *GetPrintNameForNode() = 0;

  // Print() is deliberately _not_ virtual
  // subclasses should override PrintChildren() instead
  void Print(int indentLevel, const char *label = NULL);

  // pass in the identLevel
  virtual void PrintChildren(int) {}

  // returns whether or not the node is capable of returning
  virtual bool return_now(CodeGenerator *codegen = nullptr,
                          Frame_allocator *frame_allocator = nullptr,
                          Symbol_table *symbol_table = nullptr,
                          Expr *expr = nullptr) {
    return false;
  }

  virtual bool break_now(CodeGenerator *codegen = nullptr,
                         Frame_allocator *frame_allocator = nullptr,
                         Symbol_table *symbol_table = nullptr) {
    return false;
  }

  virtual bool needs_dereference() { return false; }

  // pass in the reason for analyzing
  virtual void analyze(reasonT focus) override {}

  virtual void analyze(Symbol_table *symbol_table, reasonT focus) override {
    analyze(focus);
  }

  // assigns source to the reference or frame_location of this node
  // returns the assigned location
  Location* assign(Location* source, CodeGenerator* codegen);

  Node *find_loop_node();

  Node *get_parent() { return parent; }
  Location* get_frame_location() { return frame_location; }
};

#endif /* NODE_H */
