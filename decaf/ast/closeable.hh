#ifndef CLOSEABLE_H
#define CLOSEABLE_H

class Symbol_table;

class Closeable {
  virtual void build_table() = 0;
  virtual void set_parent(Symbol_table& other) = 0;
};

#endif // CLOSEABLE_H
