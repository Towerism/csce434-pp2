#ifndef CHECKABLE_H
#define CHECKABLE_H

#include "scope_stack.hh"

class Analyzable {
  virtual void analyze(Scope_stack& scope_stack) = 0;
};

#endif // CHECKABLE
