cmake_minimum_required (VERSION 3.0)
project (RayTracer)


set (RayTracer_VERSION_MAJOR 0)
set (RayTracer_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
#add_library(il)


#include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/TextureLoader")
include_directories("${PROJECT_SOURCE_DIR}/DragonMath")
include_directories("${PROJECT_SOURCE_DIR}/WorldModel")
include_directories("${PROJECT_SOURCE_DIR}/AssetLoader")
#add_library(WorldMode)
#add_library(TextureLoaderLib TextureLoader.bin)

add_subdirectory(TextureLoader)
add_subdirectory(AssetLoader)
add_subdirectory(WorldModel)
add_subdirectory(DragonMath)


add_executable (RayTracer camera.cc driver.cc renderer.cc wireframe.cc)

install (TARGETS RayTracer DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/camera.h" DESTINATION include)
install (FILES "${PROJECT_BINARY_DIR}/wireframe.h" DESTINATION include)
install (FILES "${PROJECT_BINARY_DIR}/renderer.h" DESTINATION include)
target_link_libraries (RayTracer TextureLoader)
target_link_libraries (RayTracer WorldModel)
target_link_libraries (RayTracer DragonMath)
target_link_libraries (RayTracer AssetLoader)
#target_link_libraries (RayTracer assimp)

