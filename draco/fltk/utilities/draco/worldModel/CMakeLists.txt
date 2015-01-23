cmake_minimum_required (VERSION 2.8)



##  meta data  ##
project (WorldModel)

set (WorldModel_VERSION_MAJOR 0)
set (WorldModel_VERSION_MINOR 1)

include("../../../CMake/paths.cmake")

set(LIBRARY_NAME WorldModel)
set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )

add_definitions(-DDLL_EXPORT_DRACO_WORLD_MODEL)



##  source files  ##
file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/*.cc
	${PROJECT_SOURCE_DIR}/*.h)



##  UNIX directives  ##
if (UNIX)
	set (CUSTOM_FLAGS "-Wfatal-errors -Wextra -pedantic -O3")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")
	
endif(UNIX)




##  dependencies  ##
include_directories(${UTILITIES_DIR}/draco/DragonMath/)
include_directories(${UTILITIES_DIR}/draco/TextureLoader/)

find_package(OpenGL REQUIRED)

set(LIBS ${LIBS} ${OPENGL_gl_LIBRARY})




##  deliverables  ##
add_library (${LIBRARY_NAME} SHARED ${SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "")
target_link_libraries(${LIBRARY_NAME} ${LIBS})

if (MSVC)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "/DELAYLOAD:dracoUtil.dll")
endif (MSVC)
