set(AST_SRCS
  ast.cc
  ast_decl.cc
  ast_expr.cc
  ast_stmt.cc
  ast_type.cc
  scope.cc
  scope_stack.cc
  symbol_table.cc
  )

add_library(ast OBJECT ${AST_SRCS})
