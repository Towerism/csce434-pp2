// This node class is designed to represent a portion of the tree that
// encountered syntax errors during parsing. The partial completed tree
// is discarded along with the states being popped, and an instance of
// the Error class can stand in as the placeholder in the parse tree
// when your parser can continue after an error.

#include "node.hh"

class Error : public Node
{
public:
  Error() : Node() {}
  const char *GetPrintNameForNode()   { return "Error"; }
};
