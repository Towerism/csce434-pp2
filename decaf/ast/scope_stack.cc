#include "scope_stack.hh"

void Scope_stack::push() {
  scopes.push_front(new Scope);
}

void Scope_stack::pop() {
  scopes.pop_front();
}

bool Scope_stack::declare(Decl* declaration) {
  auto current_scope = scopes.front();
  return current_scope->declare(declaration);
}
