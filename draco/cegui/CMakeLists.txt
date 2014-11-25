cmake_minimum_required (VERSION 2.8)
project (Draco)

#enable_testing()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules/")

#find_package(CEGUI REQUIRED)

set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -lpthread -O3")
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)
set (Draco_VERSION_MAJOR 0)
set (Draco_VERSION_MINOR 1)

set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS}")
#set(LIBS ${LIBS} ${CEGUI_LIBRARIES})

#link_libraries(cegui-0.8.3/build/lib/libCEGUIBase-0.so)
#add_subdirectory(cegui-0.8.3/build/lib/)

#link_directories(cegui-0.8.3/build/lib/)

#link_libraries(libCEGUIBase-0.so)
#link_libraries(/home/cullenh/cegui/cegui-0.8.3/build/lib/libCEGUIBase-0.so)
#set(CEGUI_LIBRARIES "libCEGUIBase-0.so")
#set(LIBS ${LIBS} ${CEGUI_LIBRARIES})


#add_library(lib libCEGUIBase-0.so)
#include_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories("${PROJECT_SOURCE_DIR}/cegui-0.8.3/cegui/include/")
link_directories("${PROJECT_SOURCE_DIR}/cegui-0.8.3/lib/")
#add_library(lib SHARED libCEGUIBase-0.so)
#add_subdirectory(cegui-0.8.3)

add_executable (ceguiTest ${SOURCES})


target_link_libraries(ceguiTest libCEGUIBase-0.so)

#target_link_libraries(ceguiTest ${LIBS})
