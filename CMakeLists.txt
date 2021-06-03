cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

project (sliding_tile)
file (GLOB SOURCES "src/*.cpp" "src/*.h")
add_executable (sliding_tile ${SOURCES})
