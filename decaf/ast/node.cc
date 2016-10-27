#include "node.hh"

#include <stdio.h> // printf

#include <ast/expr/expr.hh>
#include <codegen/codegen.hh>
#include <codegen/frame_allocator.hh>

#include "symbol_table.hh"

Node::Node(yyltype loc) {
  location = new yyltype(loc);
  parent = NULL;
}

Node::Node() {
  location = NULL;
  parent = NULL;
}

/* The Print method is used to print the parse tree nodes.
 * If this node has a location (most nodes do, but some do not), it
 * will first print the line number to help you match the parse tree
 * back to the source text. It then indents the proper number of levels
 * and prints the "print name" of the node. It then will invoke the
 * virtual function PrintChildren which is expected to print the
 * internals of the node (itself & children) as appropriate.
 */
void Node::Print(int indentLevel, const char *label) {
  const int numSpaces = 3;
  printf("\n");
  if (GetLocation())
    printf("%*d", numSpaces, GetLocation()->first_line);
  else
    printf("%*s", numSpaces, "");
  printf("%*s%s%s: ", indentLevel * numSpaces, "", label ? label : "",
         GetPrintNameForNode());
  PrintChildren(indentLevel);
}

Node *Node::find_loop_node() {
  auto current = this;
  do {
    if (current->is_break_node)
      return current;
    current = current->parent;
  } while (current != nullptr);
  return nullptr;
}
