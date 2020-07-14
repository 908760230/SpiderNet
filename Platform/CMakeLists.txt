message(STATUS "src This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "src This is SOURCE dir " ${PROJECT_SOURCE_DIR})

aux_source_directory(. DIR_PLATFORM)


add_library(Platform_lib ${DIR_PLATFORM})