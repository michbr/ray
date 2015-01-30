cmake_minimum_required (VERSION 2.8)

##  meta data  ##
project (TextureLoader)

set (TextureLoader_VERSION_MAJOR 0)
set (TextureLoader_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME TextureLoader)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

add_definitions(-DDLL_EXPORT_DRACO_WORLD_MODEL)



##  source files  ##
file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/*.cc
        ${PROJECT_SOURCE_DIR}/*.h
)



##  UNIX directives  ##
if (UNIX)
        set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")

endif(UNIX)



##  dependencies  ##
if (UNIX)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules/")
	find_package(DevIL REQUIRED)
	include_directories(${IL_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${IL_LIBRARIES})
else (UNIX)
	set(DEVIL_DIR ${UTILITIES_DIR}/devIL-1.7.8)
	find_library(IL_LIBRARIES DevIL
	PATHS ${DEVIL_DIR})
	include_directories(${DEVIL_DIR}/include)
endif (UNIX)




##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

target_link_libraries (${LIBRARY_NAME} ${LIBS})

if (MSVC)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "/DELAYLOAD:dracoUtil.dll")
endif (MSVC)
