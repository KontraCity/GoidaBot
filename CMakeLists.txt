## --- Project configuration --- ##
cmake_minimum_required(VERSION 3.20)
project(GoidaBot)

## --- Compiler configuration --- ##
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
include_directories("include/")

## --- Packages configuration --- ##
find_package(fmt CONFIG REQUIRED)

## --- Executable configuration  --- ##
add_executable(GoidaBot "source/main.cpp")
target_link_libraries(GoidaBot PRIVATE fmt::fmt)
