cmake_minimum_required(VERSION 3.10)
project(ML_CPP)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(ML_CPP ${SOURCES})
