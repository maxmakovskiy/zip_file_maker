cmake_minimum_required(VERSION 3.11)

project(zip_maker)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CSS_FLAGS_DEBUG "-g")
set(CMAKE_CSS_FLAGS_RELEASE "-O2")

add_executable(main
    src/main.cpp
)

