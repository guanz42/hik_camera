cmake_minimum_required(VERSION 3.0)

add_executable(sdk_demo main.cpp)

include_directories(../include/hik)

find_library(HKNETSDK NAMES hcnetsdk PATHS "../lib/")
message(STATUS "Library path HKNETSDK is " ${HKNETSDK})

target_link_libraries(sdk_demo ${HKNETSDK})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
