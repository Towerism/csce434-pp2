#ifndef CHECKABLE_H
#define CHECKABLE_H

#include <util/errors.hh>
#include "scope_stack.hh"

class Analyzable {
  virtual void analyze(Scope_stack& scope_stack) = 0;
  virtual void analyze(Scope_stack& scope_stack, reasonT focus) = 0;
};

#endif // CHECKABLE
