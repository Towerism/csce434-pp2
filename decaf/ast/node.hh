#ifndef NODE_H
#define NODE_H

#include <parse/location.hh>
#include <util/errors.hh>

#include "analyzable.hh"

class Node : public Analyzable
{
protected:
  yyltype *location;
  Node *parent;

public:
  Node(yyltype loc);
  Node();

  yyltype *GetLocation()   { return location; }
  void SetParent(Node *p)  { parent = p; }
  Node *GetParent()        { return parent; }

  virtual const char *GetPrintNameForNode() = 0;

  // Print() is deliberately _not_ virtual
  // subclasses should override PrintChildren() instead
  void Print(int indentLevel, const char *label = NULL);
  virtual void PrintChildren(int indentLevel)  {}

  virtual void analyze(reasonT focus) override {}
};

#endif /* NODE_H */
