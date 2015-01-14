
cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (Draco-Util)

set (Draco-Util_VERSION_MAJOR 0)
set (Draco-Util_VERSION_MINOR 1)

include(../../../CMake/paths.cmake)

set(LIBRARY_NAME dracoUtil)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")

add_definitions(-DDLL_EXPORT_DRACO_UTIL)



##  source files  ##
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/source/*.cc"
	"${PROJECT_SOURCE_DIR}/*.h")



##  UNIX directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})

	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")
	
endif(UNIX)



##  dependencies  ##
include_directories(
	${FLTK_DIR}
)

find_library(FLTK_LIBRARIES fltk
PATHS ${FLTK_DIR})
set(LIBS ${LIBS} ${FLTK_LIBRARIES})



##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})
