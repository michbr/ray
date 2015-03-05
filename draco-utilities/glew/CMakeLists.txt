if ( NOT DEFINED CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type" )
endif ()

project (glew)

cmake_minimum_required (VERSION 2.4)

if (COMMAND cmake_policy)
  cmake_policy (SET CMP0003 NEW)
endif()

option (BUILD_UTILS "utilities" ON)

set (GLEW_VERSION "1.12.0")

set (GLEW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glew)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32)
  set (GLEW_LIB_NAME glew32)
else ()
  set (GLEW_LIB_NAME GLEW)
  set (DLL_PREFIX lib)
endif ()

find_package (OpenGL REQUIRED)
set (GLEW_LIBRARIES ${OPENGL_LIBRARIES})

add_definitions (-DGLEW_BUILD -DGLEW_NO_GLU)

include_directories (${GLEW_DIR}/include)

add_library (glew SHARED ${GLEW_DIR}/auto/src/glew.rc)
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
set (cflags "-DGLEW_MX")
set (libname ${GLEW_LIB_NAME}mx)
configure_file (${GLEW_DIR}/glew.pc.in ${GLEW_DIR}/glewmx.pc @ONLY)

install(FILES ${GLEW_DIR}/glew.pc ${GLEW_DIR}/glewmx.pc
        DESTINATION lib/pkgconfig
)
