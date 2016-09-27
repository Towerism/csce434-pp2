#ifndef STMT_H
#define STMT_H

#include <ast/node.hh>
#include <ast/closeable.hh>

class Stmt : public Node, public Closeable
{
public:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
  virtual void build_table() override {}
};

#endif /* STMT_H */
