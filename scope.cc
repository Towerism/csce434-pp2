#include "scope.hh"

bool Scope::declare(Decl* declaration) {
  if (conflict_exists_with(declaration))
    return false;
  declarations[declaration] = declaration;
  return true;
}

bool Scope::conflict_exists_with(Decl* declaration) {
  auto iterator = declarations.find(declaration);
  return iterator != declarations.end();
}
