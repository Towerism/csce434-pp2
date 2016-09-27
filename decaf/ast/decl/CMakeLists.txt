set(DECL_SRCS
  decl.cc
  class_decl.cc
  fn_decl.cc
  var_decl.cc
  interface_decl.cc
  )

add_library(decl OBJECT ${DECL_SRCS})
