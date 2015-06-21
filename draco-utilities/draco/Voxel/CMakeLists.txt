cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (DracoVoxel)

set(CMAKE_BUILD_TYPE Release)

set (DracoVoxel_VERSION_MAJOR 0)
set (DracoVoxel_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME DracoVoxel)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

add_definitions(-DDLL_EXPORT_DRACO_VOXEL)



##  source files  ##
file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/source/**.cc
	${PROJECT_SOURCE_DIR}/source/*/*.cc
	${PROJECT_SOURCE_DIR}/**.h
	${PROJECT_SOURCE_DIR}/*/*.h
)



##  compiler directives ##
if (UNIX)
	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
endif(UNIX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")



##  dependencies  ##
include_directories(
	${PROJECT_SOURCE_DIR}
	${UTILITIES_DIR}/draco/
)
set(LIBS ${LIBS} DragonMath WorldModel)



##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries(${LIBRARY_NAME} ${LIBS})

