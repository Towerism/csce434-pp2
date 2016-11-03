set(CODEGEN_SRCS
  codegen.cc
  complex_op_factory.cc
  error_message_factory.cc
  frame_allocator.cc
  label_transformer.cc
  linker.cc
  )

add_library(codegen ${CODEGEN_SRCS}
  )

set(CODEGEN_LIBS
  arch
  )

target_link_libraries(codegen ${CODEGEN_LIBS})
