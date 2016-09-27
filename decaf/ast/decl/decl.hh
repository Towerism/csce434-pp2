#ifndef DECL_H
#define DECL_H

#include <ast/closeable.hh>
#include <ast/node.hh>
#include <ast/identifier.hh>

class Decl : public Node, public Closeable
{
protected:
  Identifier *id;

public:
  Decl(Identifier *name);
  std::string getName() const { return id->getName(); }
  virtual void build_table() override {}

  friend std::ostream& operator<<(std::ostream& out, Decl* decl) {
    return out << decl->getName();
  }
};

#endif /* DECL_H */
