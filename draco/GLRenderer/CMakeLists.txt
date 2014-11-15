cmake_minimum_required (VERSION 3.0)
project (GLRenderer)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-std=c++11 -lGL -lX11 ${CMAKE_CXX_FLAGS}")
set (GLRenderer_VERSION_MAJOR 0)
set (GLRenderer_VERSION_MINOR 1)

add_executable (GLRenderer ${SOURCES})
