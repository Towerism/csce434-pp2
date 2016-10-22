set(CODEGEN_SRCS
  codegen.cc
  frame_allocator.cc
  )

add_library(codegen ${CODEGEN_SRCS}
  )

set(CODEGEN_LIBS
  arch
  )

target_link_libraries(codegen ${CODEGEN_LIBS})
