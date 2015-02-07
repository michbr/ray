cmake_minimum_required (VERSION 2.8)

##  meta data  ##
project (GLRenderer)

set(CMAKE_BUILD_TYPE Release)

set (GLRenderer_VERSION_MAJOR 0)
set (GLRenderer_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME GLRenderer)
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
        ${PROJECT_SOURCE_DIR}/source/*.cc
        ${PROJECT_SOURCE_DIR}/*.h)

##  compiler directives ##
if (UNIX)
        set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
endif(UNIX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")

##  dependencies  ##
include_directories(${UTILITIES_DIR}/draco/worldModel/)
include_directories(${UTILITIES_DIR}/draco/DragonMath/)

include_directories(${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)

set(LIBS ${LIBS} ${OPENGL_gl_LIBRARY})

#IF (UNIX)
#	find_package(X11)
#	set(LIBS ${LIBS} ${X11_LIBRARIES})
#ENDIf()

##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries(${LIBRARY_NAME} ${LIBS})

