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

add_custom_command(
  TARGET dcc
  POST_BUILD
  COMMAND cp $<TARGET_FILE:dcc> ${CMAKE_SOURCE_DIR}/.
  COMMENT "Copying executable to project root"
  )

set_directory_properties(PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES
  "${CMAKE_SOURCE_DIR}/dcc"
  )
