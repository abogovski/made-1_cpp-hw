cmake_minimum_required(VERSION 3.10.0)
project(bin)

set(C_CXX_WARNINGS "-Wall -Wpedantic -Wdeprecated -Wextra -Werror")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${C_CXX_WARNINGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${C_CXX_WARNINGS})

add_executable(match_first_car "${PROJECT_SOURCE_DIR}/main.c")
target_link_libraries(match_first_car lib)
