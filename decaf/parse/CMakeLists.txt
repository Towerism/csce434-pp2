set(FLEX_INPUT ${CMAKE_CURRENT_LIST_DIR}/scanner.l)
set(FLEX_GENERATED ${CMAKE_CURRENT_LIST_DIR}/lex.cc)
if(FLEX_FOUND)
  add_custom_command(
    OUTPUT ${FLEX_GENERATED}
    COMMAND ${FLEX_EXECUTABLE} -d -o ${FLEX_GENERATED} ${FLEX_INPUT}
    )
endif()

set(BISON_INPUT ${CMAKE_CURRENT_LIST_DIR}/parser.y)
set(BISON_GENERATED ${CMAKE_CURRENT_LIST_DIR}/parse.cc)
set(BISON_HEADER ${CMAKE_CURRENT_LIST_DIR}/parse.hh)
set(BISON_OUTPUT ${CMAKE_CURRENT_LIST_DIR}/parse.output)
if(BISON_FOUND)
  add_custom_command(
    OUTPUT ${BISON_GENERATED}
    COMMAND ${BISON_EXECUTABLE} -dvty ${BISON_INPUT} -o ${BISON_GENERATED}
    DEPENDS ${FLEX_GENERATED}
    )
endif()

set_source_files_properties(${FLEX_GENERATED} GENERATED)
set_source_files_properties(${BISON_GENERATED} GENERATED)
set_source_files_properties(${BISON_HEADER} GENERATED)
set_source_files_properties(${BISON_OUTPUT} GENERATED)
set_directory_properties(PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES
  "${FLEX_GENERATED};${BISON_GENERATED};${BISON_HEADER};${BISON_OUTPUT}"
  )


set(PARSE_SRCS
  ${BISON_GENERATED}
  ${FLEX_GENERATED}
  )

set(PARSE_LIBS
  ast
  util
  )
add_library(parse ${PARSE_SRCS})
target_link_libraries(parse ${PARSE_LIBS})
