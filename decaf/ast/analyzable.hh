#ifndef CHECKABLE_H
#define CHECKABLE_H

#include <util/errors.hh>

class Analyzable {
  virtual void analyze(reasonT focus) = 0;
};

#endif // CHECKABLE
