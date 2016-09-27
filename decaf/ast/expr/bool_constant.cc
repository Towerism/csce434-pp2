#include "bool_constant.hh"

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
  value = val;
}

void BoolConstant::PrintChildren(int indentLevel) {
  printf("%s", value ? "true" : "false");
}
