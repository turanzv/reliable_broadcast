cmake_minimum_required(VERSION 3.10)
project(ReliableBroadcast)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add source files
add_executable(ReliableBroadcastApp src/main.cpp)

# Ensure that the include directory is used for header files
target_include_directories(ReliableBroadcastApp PRIVATE include)

# Enable testing
enable_testing()
add_subdirectory(tests)