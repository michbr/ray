cmake_minimum_required (VERSION 2.8)


##  meta data  ##
project (Draco-rayTracer)

set (Draco-rayTracer_VERSION_MAJOR 0)
set (Draco-rayTracer_VERSION_MINOR 1)

include(../CMake/paths.cmake)

set (LIBRARY_NAME rayTracer.ds)
set (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../scales")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

set(WORLD_MODEL_DIR "${UTILITIES_DIR}/draco/worldModel")
set(TEXTURE_LOADER_DIR "${UTILITIES_DIR}/draco/TextureLoader")
set(DRAGONMATH_DIR "${UTILITIES_DIR}/draco/DragonMath")
set(ASSET_LOADER_DIR "${UTILITIES_DIR}/draco/AssetLoader")
set(RAY_TRACER_DIR "${UTILITIES_DIR}/draco/RayTracer")
set(IMAGE_DIR "${UTILITIES_DIR}/draco/Image")
set(DRACO_COMMON_DIR "${UTILITIES_DIR}/draco/common")

##  source files  ##

file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/*.cc"
        "${PROJECT_SOURCE_DIR}/*.h"
)


##  compiler directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})
	set (CUSTOM_FLAGS "-Wall -Wextra -pedantic -O3")
endif(UNIX)
if(WIN32)
        add_definitions(-DWIN32)
endif(WIN32)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")

##  dependencies  ##
include_directories(
	${WORLD_MODEL_DIR}
	${TEXTURE_LOADER_DIR}
	${DRAGONMATH_DIR}
	${ASSET_LOADER_DIR}
	${RAY_TRACER_DIR}
	${IMAGE_DIR}
	${DRACO_COMMON_DIR}
        ${FLTK_DIR}
        ${BASE_DIR}
)

if (UNIX)
    find_library(FLTK_LIBRARIES fltk
    PATHS ${FLTK_DIR})
else (UNIX)
    find_library(FLTK_LIBRARIES winfltk
    PATHS ${FLTK_DIR})
    set(LIBS ${LIBS} Shlwapi)
endif (UNIX)

find_library(WORLD_MODEL_LIBRARY WorldModel
PATHS ${LIB_DIR})
find_library(RAY_TRACER_LIBRARY RayTracer
PATHS ${LIB_DIR})
find_library(ASSET_LOADER_LIBRARY AssetLoader
PATHS ${LIB_DIR})
find_library(IMAGE_LIBRARY Image
PATHS ${LIB_DIR})
find_library(DRACO_COMMON_LIBRARY DracoCommon
PATHS ${LIB_DIR})
set(LIBS ${LIBS} ${FLTK_LIBRARIES} ${WORLD_MODEL_LIBRARY} ${ASSET_LOADER_LIBRARY} ${RAY_TRACER_LIBRARY} ${IMAGE_LIBRARY} ${DRACO_COMMON_LIBRARY})

find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
if(OPENGL_FOUND)
	add_definitions(-DHAVE_GL)
	include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)


##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})
