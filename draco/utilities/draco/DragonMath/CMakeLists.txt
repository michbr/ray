cmake_minimum_required (VERSION 2.8)

##  meta data  ##
project (DragonMath)

set(CMAKE_BUILD_TYPE Release)

set (DragonMath_VERSION_MAJOR 0)
set (DragonMath_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME DragonMath)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )


add_definitions(-DDLL_EXPORT_DRACO_DRAGON_MATH)

##  source files  ##
file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/*.cc
        ${PROJECT_SOURCE_DIR}/*.h)

##  compiler directives ##
if (UNIX)
        set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")

endif(UNIX)
enable_testing()


##  dependencies  ##
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(test)

##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})
add_executable(${LIBRARY_NAME}Test ${SOURCES})


target_link_libraries(${LIBRARY_NAME} ${LIBS})
target_link_libraries(${LIBRARY_NAME}Test UnitTests gtest gtest_main)
add_test(${LIBRARY_NAME}TestBlah ${LIBRARY_NAME}Test)
