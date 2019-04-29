cmake_minimum_required(VERSION 2.8.4)

add_executable(main main.cpp)

include_directories(../include/hik)

find_library(HIKDRIVER NAMES hikdriver PATHS "../lib/")
message(STATUS "Library path HIKDRIVER is " ${HIKDRIVER})

target_link_libraries(main ${HIKDRIVER})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
