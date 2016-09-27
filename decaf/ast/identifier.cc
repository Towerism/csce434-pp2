#include "identifier.hh"

#include <string.h> // strdup
#include <stdio.h>  // printf

Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
  name = strdup(n);
}

void Identifier::PrintChildren(int indentLevel) {
  printf("%s", name);
}
