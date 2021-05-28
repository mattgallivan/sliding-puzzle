cmake_minimum_required (VERSION 2.8.11)

project (sliding_tile)
file (GLOB SOURCES "src/*.cpp" "src/*.h")
add_executable (sliding_tile ${SOURCES})
