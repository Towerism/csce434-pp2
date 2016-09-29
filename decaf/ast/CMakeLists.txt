add_subdirectory(decl)
add_subdirectory(expr)
add_subdirectory(stmt)
add_subdirectory(type)
set(AST_SRCS
  node.cc
  identifier.cc
  symbol_table.cc
  virtual_table.cc
  )

add_library(ast ${AST_SRCS}
  $<TARGET_OBJECTS:decl>
  $<TARGET_OBJECTS:expr>
  $<TARGET_OBJECTS:stmt>
  $<TARGET_OBJECTS:type>
  )
