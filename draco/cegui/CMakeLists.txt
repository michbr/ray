cmake_minimum_required (VERSION 2.8)
project (Draco)

#enable_testing()


set (CUSTOM_FLAGS "-Wfatal-errors -Wall -Wextra -pedantic -lpthread -O3")
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)
set (Draco_VERSION_MAJOR 0)
set (Draco_VERSION_MINOR 1)

set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} ${CUSTOM_FLAGS}")

#set(CEGUI_LIBRARIES libCEGUIBase-0.so)

#set(CEGUI_LIBRARIES "libCEGUIBase-0.so libCEGUICommonDialogs-0.so libCEGUICoreWindowRendererSet.so libCEGUIDevILImageCodec.so libCEGUIExpatParser.so libCEGUILibXMLParser.so libCEGUINullRenderer-0.so libCEGUISILLYImageCodec.so libCEGUISTBImageCodec.so libCEGUITGAImageCodec.so")
set(CEGUI_LIBRARIES "libCEGUIBase-0.so")

set(LIBS ${LIBS} ${CEGUI_LIBRARIES})


include_directories("${PROJECT_SOURCE_DIR}/cegui-0.8.3/cegui/include/")
link_directories("${PROJECT_SOURCE_DIR}/cegui-0.8.3/lib/")

add_executable (ceguiTest ${SOURCES})


#target_link_libraries(ceguiTest libCEGUIBase-0.so)

target_link_libraries(ceguiTest ${LIBS})
