cmake_minimum_required (VERSION 3.0)
project (AssetLoader)

set (AssetLoader_VERSION_MAJOR 0)
set (AssetLoader_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

add_library (AssetLoader loader.cc)

target_link_libraries (AssetLoader assimp)
#target_link_libraries (RayTracer TextureLoader)
