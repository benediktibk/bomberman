cmake_minimum_required(VERSION 2.8)
project(game)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_CXX_FLAGS_COMMON "-Wall -Wextra -Werror -ansi")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_COMMON} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_COMMON} -g")

add_subdirectory(common)
add_subdirectory(gameengine)
add_subdirectory(graphic)
add_subdirectory(main)
add_subdirectory(physic)
add_subdirectory(sound)
add_subdirectory(threading)