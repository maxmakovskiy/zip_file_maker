cmake_minimum_required(VERSION 3.11)

project(zip_maker)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CSS_FLAGS_DEBUG "-g")
set(CMAKE_CSS_FLAGS_RELEASE "-O2")

find_package(Boost 1.76.0 REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(zip_maker_lib STATIC
    src/coder.cpp
    src/tree.cpp
)

add_executable(main
    src/main.cpp
)

target_link_libraries(main
    zip_maker_lib
)

