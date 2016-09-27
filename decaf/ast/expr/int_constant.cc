#include "int_constant.hh"

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
  value = val;
}

void IntConstant::PrintChildren(int indentLevel) {
  printf("%d", value);
}
