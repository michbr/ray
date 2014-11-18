cmake_minimum_required (VERSION 3.0)
project (Draco)

enable_testing()

set (Draco_VERSION_MAJOR 0)
set (Draco_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
#add_library(il)


#include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/TextureLoader")
include_directories("${PROJECT_SOURCE_DIR}/DragonMath")
include_directories("${PROJECT_SOURCE_DIR}/WorldModel")
include_directories("${PROJECT_SOURCE_DIR}/AssetLoader")
include_directories("${PROJECT_SOURCE_DIR}/Main")
include_directories("${PROJECT_SOURCE_DIR}/RayTracer")
#add_library(WorldMode)
#add_library(TextureLoaderLib TextureLoader.bin)

add_subdirectory(TextureLoader)
add_subdirectory(AssetLoader)
add_subdirectory(WorldModel)
add_subdirectory(DragonMath)
add_subdirectory(Main)
add_subdirectory(RayTracer)
add_subdirectory(GLRenderer)

add_executable (Draco driver.cc)

add_executable (GL test.cc)
target_link_libraries (GL DragonMath)
target_link_libraries (GL GLRenderer)
#add_library (RayTracerTestLib SHARED camera.cc renderer.cc wireframe.cc)

#target_link_libraries(RayTracerTestLib TextureLoader)
#target_link_libraries(RayTracerTestLib DragonMath AssetLoader)
#target_link_libraries(RayTracerTestLib WorldModel)

add_executable(UnitTests main.cc)

target_link_libraries(UnitTests MainTestLib)
target_link_libraries(UnitTests WorldModelTestLib)
target_link_libraries(UnitTests DragonMath)
target_link_libraries(UnitTests TextureLoader)

add_test(Test UnitTests)

target_link_libraries (Draco Main)
target_link_libraries (Draco RayTracer)
target_link_libraries (Draco TextureLoader WorldModel)
target_link_libraries (Draco DragonMath)
target_link_libraries (Draco AssetLoader)
target_link_libraries (Draco GLRenderer)

