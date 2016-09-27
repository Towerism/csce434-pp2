#include "double_constant.hh"

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
  value = val;
}

void DoubleConstant::PrintChildren(int indentLevel) {
  printf("%g", value);
}
