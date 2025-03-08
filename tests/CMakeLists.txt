add_executable(test_rb test_rb.cpp)
add_executable(test_node test_node.cpp)

# Register tests
add_test(NAME TestRB COMMAND test_rb)
add_test(NAME TestNode COMMAND test_node)