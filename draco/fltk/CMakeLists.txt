
cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (Draco)

set (Draco_VERSION_MAJOR 0)
set (Draco_VERSION_MINOR 1)

include(CMake/paths.cmake)

#set(UTILITIES_DIR "${PROJECT_SOURCE_DIR}/utilities")
#set(SHARED_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/bin")
add_subdirectory(${UTILITIES_DIR})

set(EXECUTABLE_NAME draco)
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

add_definitions(-DDLL_IMPORT_DRACO_SCALE)

set(DRACO_UTIL_DIR "${UTILITIES_DIR}/draco")
set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")



##  source files  ##
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/*.cc"
	"${PROJECT_SOURCE_DIR}/*.h")



##  UNIX directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})
	
	#include(CMake/macros.cmake)
	#include(CMake/setup.cmake)
	include(CMake/resources.cmake)
	#include(CMake/options.cmake)
	#include(CMake/export.cmake)
	set(LIBS ${LIBS} ${EXTRA_FLTK_LIBS})

	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")
	
endif(UNIX)



##  dependencies  ##
include_directories(
	${FLTK_DIR}
	${DRACO_UTIL_DIR}
)

find_library(FLTK_LIBRARIES fltk
PATHS ${FLTK_DIR})
set(LIBS ${LIBS} ${FLTK_LIBRARIES} dracoUtil)
link_directories("${UTILITIES_DIR}/draco/util")



##  deliverables  ##
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBS})

if (MSVC)
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH} )
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH} )
endif (MSVC)
