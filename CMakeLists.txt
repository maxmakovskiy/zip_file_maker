cmake_minimum_required(VERSION 3.16)

project(zip_maker VERSION 0.1 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CSS_FLAGS_DEBUG "-g")
set(CMAKE_CSS_FLAGS_RELEASE "-O2")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_library(zip_maker_lib STATIC
    src/coder.cpp
    src/tree.cpp
)

add_executable(main
    src/main.cpp
    src/zipper_window.cc
)

target_link_libraries(main
    zip_maker_lib
    Qt6::Widgets
)

