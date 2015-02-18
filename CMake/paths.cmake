
cmake_minimum_required (VERSION 2.8)



get_filename_component(BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

set(DRACO_SOURCE_DIR "${BASE_DIR}/draco-source")
set(TARGET_DIR "${BASE_DIR}/draco")
set(UTILITIES_DIR "${BASE_DIR}/draco-utilities")
set(LIB_DIR "${TARGET_DIR}/utilities")
set(BIN_DIR "${TARGET_DIR}/bin")
set(SCALES_DIR "${BASE_DIR}/draco-scales")
set(TARGET_SCALES_DIR "${TARGET_DIR}/scales")
