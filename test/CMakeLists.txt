set(TEST_SCRIPT "./test.sh")
set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR})

add_custom_target(test-syntax
  COMMAND ${TEST_SCRIPT} $<TARGET_FILE:dcc> syntax
  WORKING_DIRECTORY ${TEST_DIR}
  )

add_custom_target(test-scope
  COMMAND ${TEST_SCRIPT} $<TARGET_FILE:dcc> scope
  WORKING_DIRECTORY ${TEST_DIR}
  )
