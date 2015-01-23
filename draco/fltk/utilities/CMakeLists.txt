
cmake_minimum_required (VERSION 2.8)



project (Draco-Utilities)

set(UTILITIES_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory("draco/util")
add_subdirectory("draco/DragonMath")
add_subdirectory("draco/TextureLoader")
add_subdirectory("draco/AssetLoader")
add_subdirectory("draco/worldModel")
