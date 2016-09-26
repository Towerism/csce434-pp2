#ifndef SCOPE_STACK_H
#define SCOPE_STACK_H

#include <deque>
#include "scope.hh"

class Scope_stack {
public:
  void push();
  void pop();

  // return true if declaration successful, false if conflict in current scope
  bool declare(Decl* declaration);

private:
  std::deque<Scope*> scopes;
};

#endif // SCOPE_STACK
