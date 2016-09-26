add_subdirectory(ast)
add_subdirectory(parse)
add_subdirectory(util)

add_library(decaf
  $<TARGET_OBJECTS:ast>
  $<TARGET_OBJECTS:parse>
  $<TARGET_OBJECTS:util>
  )
