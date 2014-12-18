cmake_minimum_required (VERSION 2.8)
project (Draco)

#enable_testing()
#find_package(OpenGL REQUIRED)

IF (UNIX)
        find_package(X11)
        set(LIBS ${LIBS} ${X11_LIBRARIES})
ENDIf()

#include(CMake/macros.cmake)
#include(CMake/setup.cmake)
include(CMake/resources.cmake)
include(CMake/options.cmake)
#include(CMake/export.cmake)

set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)
set (Draco_VERSION_MAJOR 0)
set (Draco_VERSION_MINOR 1)

set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS}")


find_library(FLTK_LIBRARIES
#set(FLTK_LIBRARIES
fltk
fltk_forms
fltk_images
fltk_z
PATHS ${PROJECT_SOURCE_DIR}/fltk-1.3.3/lib/)

set(LIBS ${LIBS} ${FLTK_LIBRARIES} ${EXTRA_FLTK_LIBS})
#set(LIBS ${LIBS} ${OPENGL_gl_LIBRARY})

include_directories("${PROJECT_SOURCE_DIR}/fltk-1.3.3/")
#link_directories("${PROJECT_SOURCE_DIR}/fltk-1.3.3/lib/")

add_executable (fltkTest ${SOURCES})


target_link_libraries(fltkTest ${LIBS})
