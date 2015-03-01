cmake_minimum_required (VERSION 2.8)

##  meta data  ##
project (AssetLoader)

set (AssetLoader_VERSION_MAJOR 0)
set (AssetLoader_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME AssetLoader)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

add_definitions(-DDLL_EXPORT_DRACO_ASSET_LOADER)


##  source files  ##
file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/*.cc
        ${PROJECT_SOURCE_DIR}/*.h)


##  compile directives  ##
if (UNIX)
        set (CUSTOM_FLAGS "-Wfatal-errors -Wextra -pedantic -O3")
endif(UNIX)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


##  dependencies  ##
include_directories(${UTILITIES_DIR}/draco/)
# TODO improve this...
include_directories(${UTILITIES_DIR}/assimp-3.1.1)

set(LIBS ${LIBS} assimp WorldModel DragonMath TextureLoader)

add_library (${LIBRARY_NAME} SHARED ${SOURCES})
target_link_libraries(${LIBRARY_NAME} ${LIBS})
