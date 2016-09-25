#ifndef CHECKABLE_H
#define CHECKABLE_H

#include "scope_stack.hh"
#include "errors.hh"

class Analyzable {
  virtual void analyze(Scope_stack& scope_stack) = 0;
  virtual void analyze(Scope_stack& scope_stack, reasonT focus) = 0;
};

#endif // CHECKABLE
