#include "string_constant.hh"

#include <cstring>

#include <util/utility.hh>

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
  Assert(val != NULL);
  value = strdup(val);
}

void StringConstant::PrintChildren(int indentLevel) {
  printf("%s",value);
}
