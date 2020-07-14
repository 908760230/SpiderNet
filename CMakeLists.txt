cmake_minimum_required(VERSION 3.8)

project(SpiderNet)

message(STATUS "root This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "root This is SOURCE dir " ${PROJECT_SOURCE_DIR})
include_directories(Platform)


add_subdirectory(ThirdParty)
add_subdirectory(Platform)
add_subdirectory(SpiderNet)



add_executable(out  main.cpp)

target_link_libraries(out SpiderNet_lib Platform_lib Common_lib)