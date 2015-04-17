cmake_minimum_required (VERSION 2.8)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(${UTILITIES_DIR}/gtest-1.7.0/include)

add_executable (${LIBRARY_NAME}Test ${SOURCES})
target_link_libraries(${LIBRARY_NAME}Test gtest gtest_main ${LIBRARY_NAME})

add_test(${LIBRARY_NAME}Test ${LIBRARY_NAME}Test)
