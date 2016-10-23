set(EXPR_SRCS
  int_constant.cc
  double_constant.cc
  bool_constant.cc
  string_constant.cc
  operator.cc
  compound_expr.cc
  logical_expr.cc
  array_access.cc
  field_access.cc
  call.cc
  new_expr.cc
  new_array_expr.cc
  this.cc
  assign_expr.cc
  arithmetic_expr.cc
  relational_expr.cc
  equality_expr.cc
  )

add_library(expr OBJECT ${EXPR_SRCS})
