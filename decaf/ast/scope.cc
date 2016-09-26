#include "scope.hh"
#include "ast_decl.hh"

bool Scope::declare(Decl* declaration) {
  if (conflict_exists_with(declaration))
    return false;
  declarations[declaration->getName()] = declaration;
  return true;
}

bool Scope::conflict_exists_with(Decl* declaration) {
  auto iterator = declarations.find(declaration->getName());
  return iterator != declarations.end();
}
