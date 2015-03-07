cmake_minimum_required (VERSION 2.4)


##  meta data  ##
project (glew)

set (glew_VERSION "1.12.0")

if ( NOT DEFINED CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type" )
endif ()

if (COMMAND cmake_policy)
  cmake_policy (SET CMP0003 NEW)
endif()

option (BUILD_UTILS "utilities" ON)


include(../../CMake/paths.cmake)

set(LIBRARY_NAME glew)

set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_DIR})

set (GLEW_DIR ${CMAKE_CURRENT_LIST_DIR}/glew)

set (GLEW_LIB_NAME glew)

find_package (OpenGL REQUIRED)
set (GLEW_LIBRARIES ${OPENGL_LIBRARIES})

add_definitions (-DGLEW_BUILD -DGLEW_NO_GLU)

include_directories (${GLEW_DIR}/include)

add_library (glew SHARED ${GLEW_DIR}/src/glew.c)
SET_TARGET_PROPERTIES(glew PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (glew ${GLEW_LIBRARIES})
set_target_properties (glew PROPERTIES OUTPUT_NAME ${GLEW_LIB_NAME})
#set_target_properties (glew PROPERTIES PREFIX "${DLL_PREFIX}")


set (prefix ${CMAKE_INSTALL_PREFIX})
set (exec_prefix \${prefix})
set (libdir \${prefix}/lib)
set (includedir \${prefix}/include)
set (includedir \${prefix}/include)
set (version ${GLEW_VERSION})
set (libname ${GLEW_LIB_NAME})
set (cflags)
set (requireslib glu)
configure_file (${GLEW_DIR}/glew.pc.in ${GLEW_DIR}/glew.pc @ONLY)

#install(FILES ${GLEW_DIR}/glew.pc ${GLEW_DIR}/glewmx.pc
#        DESTINATION lib/pkgconfig
#)
