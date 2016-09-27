#include "operator.hh"

#include <cstring>

#include <util/utility.hh>

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
  Assert(tok != NULL);
  strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) {
  printf("%s",tokenString);
}
