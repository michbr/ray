cmake_minimum_required (VERSION 3.0)
project (GUI)

set(CMAKE_BUILD_TYPE Release)

set (TextureLoader_VERSION_MAJOR 0)
set (TextureLoader_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules/")
find_package(CEGUI REQUIRED)
include_directories(${CEGUI_INCLUDE_DIR})
Message("***************** ${CEGUI_INCLUDE_DIR} *******************")
set(LIBS ${LIBS} ${CEGUI_LIBRARIES})

add_executable(test_window firstWindow.cc)

#add_library (TextureLoader SHARED textureLoader.cc texture.cc)

#target_link_libraries (TextureLoader ${LIBS})
