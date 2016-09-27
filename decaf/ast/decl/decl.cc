#include "decl.hh"

#include <util/utility.hh>

Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
  Assert(n != NULL);
  (id=n)->SetParent(this);
}
