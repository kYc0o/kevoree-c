cmake_minimum_required(VERSION 2.8)
project(kevoree-c-model)

include_directories(.)
file(GLOB_RECURSE SRC src/*.c)

add_executable(
 main
 ${SRC}
)