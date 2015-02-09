cmake_minimum_required (VERSION 3.0)
project (DragonMath)

set(CMAKE_BUILD_TYPE Release)

set (TextureLoader_VERSION_MAJOR 0)
set (TextureLoader_VERSION_MINOR 1)

add_library (DragonMath SHARED dragonmath.cc)

