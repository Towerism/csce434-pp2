#ifndef CHECKABLE_H
#define CHECKABLE_H

#include <util/errors.hh>

class Symbol_table;

class Analyzable {
  virtual void analyze(reasonT focus) = 0;
  virtual void analyze(Symbol_table* symbol_table, reasonT focus) = 0;
};

#endif // CHECKABLE
