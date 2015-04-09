cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (WorldModel)

set (WorldModel_VERSION_MAJOR 0)
set (WorldModel_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME WorldModel)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

set(DEVIL_DIR "${UTILITIES_DIR}/DevIL")

add_definitions(-DDLL_EXPORT_DRACO_WORLD_MODEL)
add_definitions(-DDLL_IMPORT_DRACO_WORLD_MODEL_RENDERER)



##  source files  ##
file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/*.cc
	${PROJECT_SOURCE_DIR}/*.h
)



##  compiler directives  ##
if (UNIX)
	set (CUSTOM_FLAGS "-Wfatal-errors -Wextra -pedantic -O3")
	
endif(UNIX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")



##  dependencies  ##
include_directories(${UTILITIES_DIR}/draco/)
include_directories(${DEVIL_DIR}/include)

set(LIBS ${LIBS} DragonMath)



##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries(${LIBRARY_NAME} ${LIBS})

