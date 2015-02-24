
cmake_minimum_required (VERSION 2.8)
cmake_policy(SET CMP0015 OLD)



##  meta data  ##
project (Draco)
enable_testing()

set (Draco_VERSION_MAJOR 0)
set (Draco_VERSION_MINOR 1)

include(CMake/paths.cmake)

add_subdirectory(${UTILITIES_DIR})
#add_subdirectory(${SCALES_DIR})

set(EXECUTABLE_NAME draco)
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_definitions(-DDLL_IMPORT_DRACO_SCALE)

set(DRACO_UTIL_DIR "${UTILITIES_DIR}/draco")
set(FLTK_DIR "${UTILITIES_DIR}/fltk-1.3.3")



##  source files  ##
file(GLOB SOURCES
	"${DRACO_SOURCE_DIR}/*.cc"
	"${DRACO_SOURCE_DIR}/*.h")



##  compiler directives  ##
if (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})

	include(CMake/resources.cmake)
	set(LIBS ${LIBS} ${EXTRA_FLTK_LIBS})

	set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -O3")
endif(UNIX)
if(WIN32)
	add_definitions(-DWIN32)
endif(WIN32)
#if(NOT MSVC)
#	set (CUSTOM_FLAGS "${CUSTOM_FLAGS} -static-libgcc -static-libstdc++")
#endif(NOT MSVC)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS} -std=c++11")



##  dependencies  ##
include_directories(
	${FLTK_DIR}
	${DRACO_UTIL_DIR}
)

if (UNIX)
	find_library(FLTK_LIBRARIES fltk
	PATHS ${FLTK_DIR})
else (UNIX)
	find_library(FLTK_LIBRARIES winfltk
    PATHS ${FLTK_DIR})
endif (UNIX)
set(LIBS ${LIBS} ${FLTK_LIBRARIES} DracoCommon)



##  deliverables  ##
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBS})

if (UNIX)
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/../utilities/")
endif (UNIX)

if (MSVC)
#	set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "/DELAYLOAD:dracoUtil.dll")
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH} )
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH} )
endif (MSVC)
