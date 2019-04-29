cmake_minimum_required(VERSION 2.8.4)

set(LIB_SRC hik_driver.cpp)

add_library(driver_dynamic SHARED ${LIB_SRC})

set_target_properties(driver_dynamic PROPERTIES OUTPUT_NAME "hikdriver")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message(STATUS "Library path HIK_DRIVER_LIB is " ${LIBRARY_OUTPUT_PATH})

find_library(HKNETSDK NAMES hcnetsdk PATHS "../lib/")
message(STATUS "Library path HKNETSDK is " ${HKNETSDK})

target_link_libraries(driver_dynamic ${HKNETSDK})

install(TARGETS driver_dynamic
        LIBRARY DESTINATION lib)
        
install(FILES ../include/hik_driver.h DESTINATION include/hik)
