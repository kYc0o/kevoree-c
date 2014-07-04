cmake_minimum_required(VERSION 2.8)
project(kevoree-c-model)

include_directories(.)
file(GLOB_RECURSE SRC src/*.c)

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")

add_executable(
 main
 ${SRC}
)