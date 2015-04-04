
cmake_minimum_required (VERSION 2.8)



project (Draco-Utilities)

set(UTILITIES_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory("glew")
add_subdirectory("DevIL")
add_subdirectory("assimp-3.1.1")

add_subdirectory("draco/AssetLoader")
add_subdirectory("draco/DragonMath")
add_subdirectory("draco/NewGLRenderer")
add_subdirectory("draco/Image")
add_subdirectory("draco/RayTracer")
add_subdirectory("draco/TextureLoader")
add_subdirectory("draco/common")
add_subdirectory("draco/worldModel")
add_subdirectory("draco/CullenRay")
add_subdirectory("draco/CullenRay2")
