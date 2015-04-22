cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (NewGLRenderer)

set(CMAKE_BUILD_TYPE Release)

set (NewGLRenderer_VERSION_MAJOR 0)
set (NewGLRenderer_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME NewGLRenderer)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

set(GLEW_DIR "${UTILITIES_DIR}/glew/glew/include")

add_definitions(-DDLL_EXPORT_NEW_GL_RENDERER)



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
include_directories(
	${UTILITIES_DIR}/draco/
	${GLEW_DIR}
	${PROJECT_SOURCE_DIR}
	${OPENGL_INCLUDE_DIR}
)

find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
	message(ERROR " OPENGL not found!!")
endif (NOT OPENGL_FOUND)

if (OPENGL_FOUND)
	message(OpenGL found, linking...)
endif(OPENGL_FOUND)

set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
set(LIBS ${LIBS} ${OPENGL_gl_LIBRARY})
set(LIBS ${LIBS} DragonMath WorldModel glew)

set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")
include_directories(${FLTK_DIR})
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
set(LIBS ${LIBS} ${FLTK_LIBRARIES})



##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries(${LIBRARY_NAME} ${LIBS})

