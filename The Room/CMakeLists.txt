cmake_minimum_required(VERSION 3.8)
project(The_Room)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Ramirez.c RamirezGameData.h RamirezGameData.c)
add_executable(The_Room ${SOURCE_FILES})