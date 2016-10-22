set(TEST_SCRIPT "./test.sh")
set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR})

add_custom_target(run-tests
  DEPENDS  test-syntax test-semantic test-codegen
  )

add_custom_target(test-codegen
  COMMAND ${TEST_SCRIPT} $<TARGET_FILE:dcc> codegen
  WORKING_DIRECTORY ${TEST_DIR}
  COMMENT "Running codegen tests"
  )

add_custom_target(test-semantic
  COMMAND ${TEST_SCRIPT} $<TARGET_FILE:dcc> semantic
  WORKING_DIRECTORY ${TEST_DIR}
  COMMENT "Running semantic analysis tests"
  )

add_custom_target(test-syntax
  COMMAND ${TEST_SCRIPT} $<TARGET_FILE:dcc> syntax
  WORKING_DIRECTORY ${TEST_DIR}
  COMMENT "Running syntax analysis tests"
  )
