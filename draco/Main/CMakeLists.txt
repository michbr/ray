cmake_minimum_required (VERSION 3.0)
project (Main)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

add_subdirectory(test)

#add_test(WorldModelTest)
add_library (MainTestLib SHARED ${SOURCES})
target_link_libraries(MainTestLib RayTracerTest)

add_library (Main SHARED ${SOURCES})
