#ifndef SCOPE_H
#define SCOPE_H

#include <unordered_map>

class Decl;

class Scope {
public:
  // return true if declaration successful, false if local conflict
  bool declare(Decl* declaration);
private:
  std::unordered_map<Decl*, Decl*> declarations;

  bool conflict_exists_with(Decl* declaration);
};

#endif // SCOPE_H
