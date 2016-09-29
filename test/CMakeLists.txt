set(TEST_SCRIPT "./test.sh")
set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR})

add_custom_target(run-tests
  DEPENDS  test-syntax test-semantic
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
