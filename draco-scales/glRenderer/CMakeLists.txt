cmake_minimum_required (VERSION 2.8)

##  meta data  ##
project (Draco-GLRenderer)

set (Draco-GLRenderer_VERSION_MAJOR 0)
set (Draco-GLRenderer_VERSION_MINOR 1)

include(../../CMake/paths.cmake)

set (LIBRARY_NAME GLRenderer.ds)
set (LIBRARY_OUTPUT_PATH ${TARGET_SCALES_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")

##  source files  ##
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/*.cc"
	"${PROJECT_SOURCE_DIR}/*.h"
)


##  compiler directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})
	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
endif(UNIX)
if(WIN32)
	add_definitions(-DWIN32)
endif(WIN32)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")


##  dependencies  ##
include_directories(${UTILITIES_DIR}/draco/)
include_directories(
	${FLTK_DIR}
	${DRACO_SOURCE_DIR}
)

if (UNIX)
	find_library(FLTK_LIBRARIES fltk
	PATHS ${FLTK_DIR})
else (UNIX)
    find_library(FLTK_LIBRARIES winfltk
    PATHS ${FLTK_DIR})
    set(LIBS ${LIBS} Shlwapi)
endif (UNIX)
set(LIBS ${LIBS} ${FLTK_LIBRARIES})

find_library(FLTK_GL_LIBRARY fltk_gl
PATHS ${FLTK_DIR})
set(LIBS ${LIBS} ${FLTK_GL_LIBRARY})


find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
if(OPENGL_FOUND)
	add_definitions(-DHAVE_GL)
	include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)

set(LIBS ${LIBS} DracoCommon)

set(LIBS ${LIBS} NewGLRenderer)

##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})
