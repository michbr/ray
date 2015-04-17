cmake_minimum_required (VERSION 2.8)
project (UnitTests)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

set (WorldModelTest_VERSION_MAJOR 0)
set (WorldModelTest_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(${UTILITIES_DIR}/gtest-1.7.0/include)

add_library (UnitTests SHARED ${SOURCES})
target_link_libraries(UnitTests gtest gtest_main)
