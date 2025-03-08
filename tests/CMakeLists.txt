add_executable(test_rb test_rb.cpp)
add_executable(test_node test_node.cpp)

# Link tests with the main project
target_link_libraries(test_rb ReliableBroadcast)
target_link_libraries(test_node ReliableBroadcast)

# Register tests
add_test(NAME TestRB COMMAND test_rb)
add_test(NAME TestNode COMMAND test_node)