cmake_minimum_required (VERSION 3.0)
project (WorldModel)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

set (WorldModel_VERSION_MAJOR 0)
set (WorldModel_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

add_subdirectory(test)

#add_test(WorldModelTest)
add_library (WorldModelTestLib SHARED ${SOURCES})
target_link_libraries(WorldModelTestLib WorldModelTest)

add_library (WorldModel SHARED ${SOURCES})
