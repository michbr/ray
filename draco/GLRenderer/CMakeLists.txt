cmake_minimum_required (VERSION 3.0)
project (GLRenderer)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

find_package(OpenGL)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set (GLRenderer_VERSION_MAJOR 0)
set (GLRenderer_VERSION_MINOR 1)

set(LIBS ${LIBS} ${OPENGL_gl_LIBRARY})


#IF(OPENGL_FOUND)
add_library (GLRenderer ${SOURCES})
IF (UNIX)
	find_package(X11)
	set(LIBS ${LIBS} ${X11_LIBRARIES})
ENDIf()
target_link_libraries(GLRenderer ${LIBS})
#ENDIF()

#target_link_libraries(GLRenderer X11)

