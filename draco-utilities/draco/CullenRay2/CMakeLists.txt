
cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (Draco-CullenRay2)

set (Draco-CullenRay2_VERSION_MAJOR 0)
set (Draco-CullenRay2_VERSION_MINOR 1)

include(../../../CMake/paths.cmake)

set(LIBRARY_NAME DracoCullenRay2)

if (UNIX)
	set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
else (UNIX)
	set(LIBRARY_OUTPUT_PATH ${BIN_DIR})
endif (UNIX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

add_definitions(-DDLL_EXPORT_DRACO_CULLEN_RAY2)



##  source files  ##
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/source/*.cc"
	"${PROJECT_SOURCE_DIR}/*.h"
)



##  compiler directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})

	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3 -mssse3 -mfpmath=sse -flto")
endif(UNIX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")



##  dependencies  ##
include_directories(${UTILITIES_DIR}/draco/DragonMath/)

##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries(${LIBRARY_NAME} ${LIBS})
