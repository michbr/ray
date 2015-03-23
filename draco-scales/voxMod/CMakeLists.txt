
cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (Draco-VoxMod)

set (Draco-VoxMod_VERSION_MAJOR 0)
set (Draco-VoxMod_VERSION_MINOR 1)

include("../../CMake/paths.cmake")

set (LIBRARY_NAME VoxMod.ds)
set (LIBRARY_OUTPUT_PATH ${TARGET_SCALES_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH} )
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
#set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

set(DRACO_UTILITIES_DIR "${UTILITIES_DIR}/draco")
set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")



##  source files  ##
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/*.cc"
	"${PROJECT_SOURCE_DIR}/*.h")



##  compiler directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})

	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS}")
	
endif(UNIX)
if(WIN32)
	add_definitions(-DWIN32)
endif(WIN32)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



##  dependencies  ##
include_directories(
	${DRACO_SOURCE_DIR}
	${DRACO_UTILITIES_DIR}
	${FLTK_DIR}
)
if (UNIX)
	find_library(FLTK_LIBRARIES fltk
	PATHS ${FLTK_DIR})
else (UNIX)
	find_library(FLTK_LIBRARIES winfltk
    PATHS ${FLTK_DIR})
endif (UNIX)

find_library(FLTK_GL_LIBRARY fltk_gl
PATHS ${FLTK_DIR})

find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
if(OPENGL_FOUND)
	add_definitions(-DHAVE_GL)
	include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)

set(LIBS ${LIBS} ${FLTK_LIBRARISE} ${FLTK_GL_LIBRARY} DracoCommon DracoVoxel NewGLRenderer)



##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})

