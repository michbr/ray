cmake_minimum_required (VERSION 3.0)
project (WorldModelTest)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

set (WorldModelTest_VERSION_MAJOR 0)
set (WorldModelTest_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")


add_library (WorldModelTest SHARED ${SOURCES})
#add_executable(WorldModelTest WorldModelTest.cc main.cc)
target_link_libraries(WorldModelTest gtest)


