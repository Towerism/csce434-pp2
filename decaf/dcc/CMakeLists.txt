add_executable(dcc
  dcc.cc
  )

set(DCC_LIBS
  ast
  parse
  util
  -lm
  )
target_link_libraries(dcc ${DCC_LIBS})
