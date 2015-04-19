
cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (Draco-Common)

set (Draco-Common_VERSION_MAJOR 0)
set (Draco-Common_VERSION_MINOR 1)

include(../../../CMake/paths.cmake)

set(LIBRARY_NAME DracoCommon)

if (UNIX)
	set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
else (UNIX)
	set(LIBRARY_OUTPUT_PATH ${BIN_DIR})
endif (UNIX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_DIR})

set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")

add_definitions(-DDLL_EXPORT_DRACO_COMMON)

##  source files  ##
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/source/*.cc"
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
	${PROJECT_SOURCE_DIR}
	${DRACO_SOURCE_DIR}
	${UTILITIES_DIR}/draco/
)

if (UNIX)
	find_library(FLTK_LIBRARIES fltk
	PATHS ${FLTK_DIR})
	find_library(FLTK_GL_LIBRARY fltk_gl
	PATHS ${FLTK_DIR})
	set(LIBS ${LIBS} ${FLTK_GL_LIBRARY})
else (UNIX)
	find_library(FLTK_LIBRARIES winfltk
	PATHS ${FLTK_DIR})
	set(LIBS ${LIBS} Shlwapi)
	add_definitions(-DFL_DLL)
endif (UNIX)
set(LIBS ${LIBS} ${FLTK_LIBRARIES} DragonMath)


find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
if(OPENGL_FOUND)
	add_definitions(-DHAVE_GL)
	include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)


##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries(${LIBRARY_NAME} ${LIBS})
