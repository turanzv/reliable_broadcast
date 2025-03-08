cmake_minimum_required(VERSION 3.10)
project(ReliableBroadcast)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Create a STATIC library or core functionality
add_library(ReliableBroadcast STATIC
    src/ReliableBroadcast.cpp
    src/Node.cpp
    src/Network.cpp
)

# Add source files
add_executable(ReliableBroadcastApp src/main.cpp)

# Enable testing
enable_testing()
add_subdirectory(tests)