#ifndef NODE_H
#define NODE_H

#include <parse/location.hh>
#include <util/errors.hh>

#include "analyzable.hh"

class CodeGenerator;
class Frame_allocator;

class Node : public Analyzable {
protected:
  yyltype *location;
  Node *parent;
  bool is_break_node = false;

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

  // pass in the reason for analyzing
  virtual void analyze(reasonT focus) override {}

  virtual void analyze(Symbol_table *symbol_table, reasonT focus) override {
    analyze(focus);
  }

  Node *find_loop_node();

  Node* get_parent() { return parent; }
};

#endif /* NODE_H */
