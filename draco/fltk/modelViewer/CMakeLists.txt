
cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (Draco-modelViewer)

set (Draco-startTab_VERSION_MAJOR 0)
set (Draco-startTab_VERSION_MINOR 1)

include(../CMake/paths.cmake)

set (LIBRARY_NAME modelViewer.ds)
set (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../scales")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

#add_definitions(-DDLL_IMPORT_DRACO_SCALE)

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
include_directories(
	${FLTK_DIR}
	${BASE_DIR}
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

find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
if(OPENGL_FOUND)
	add_definitions(-DHAVE_GL)
	include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)



##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})
