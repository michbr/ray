cmake_minimum_required (VERSION 3.0)
project (RayTracerTest)


set (RayTracerTest_VERSION_MAJOR 0)
set (RayTracerTest_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

add_library (RayTracerTest SHARED driverTest.cc)
#add_executable(RayTracerTest driverTest.cc main.cc)
target_link_libraries(RayTracerTest gtest)

