cmake_minimum_required (VERSION 2.8)

project (Draco-startTab)

set (Draco-startTab_VERSION_MAJOR 0)
set (Draco-startTab_VERSION_MINOR 1)

set (LIBRARY_NAME startTab.ds)
set (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../scales")


if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})
	
	#include(CMake/macros.cmake)
	#include(CMake/setup.cmake)
	#include(CMake/resources.cmake)
	#include(CMake/options.cmake)
	#include(CMake/export.cmake)
	#set(LIBS ${LIBS} ${EXTRA_FLTK_LIBS})

	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")
	
	find_library(FLTK_LIBRARIES
	fltk
	fltk_forms
	fltk_images
	fltk_z
	PATHS ${PROJECT_SOURCE_DIR}/../fltk-1.3.3/lib/)

else(UNIX)
	find_library(FLTK_LIBRARIES
	fltkdll
	PATHS ${PROJECT_SOURCE_DIR}/../fltk-1.3.3/lib/)
	
endif(UNIX)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cc" "${PROJECT_SOURCE_DIR}/*.h")

set(LIBS ${LIBS} ${FLTK_LIBRARIES})

include_directories("${PROJECT_SOURCE_DIR}/../fltk-1.3.3/")
include_directories("${PROJECT_SOURCE_DIR}/../")
#link_directories("${PROJECT_SOURCE_DIR}/fltk-1.3.3/lib/")

add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})
