set(STMT_SRCS
  program.cc
  stmt_block.cc
  conditional_stmt.cc
  for_stmt.cc
  while_stmt.cc
  if_stmt.cc
  case_stmt.cc
  default_stmt.cc
  switch_stmt.cc
  return_stmt.cc
  print_stmt.cc
  )

add_library(stmt OBJECT ${STMT_SRCS})

