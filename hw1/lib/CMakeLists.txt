cmake_minimum_required(VERSION 3.10.0)
project(lib)


set(C_CXX_WARNINGS "-Wall -Wpedantic -Wdeprecated -Wextra -Werror")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${C_CXX_WARNINGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${C_CXX_WARNINGS})

option(ENABLE_COVERAGE "Enable coverage" OFF)
if (ENABLE_COVERAGE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
else (ENABLE_COVERAGE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif (ENABLE_COVERAGE)

file(GLOB LIB_SRCS "${PROJECT_SOURCE_DIR}/*.c")

add_library(lib ${LIB_SRCS})
target_include_directories(lib PUBLIC "${PROJECT_SOURCE_DIR}/include")
if (ENABLE_COVERAGE)
  target_link_libraries(lib gcov)
endif()
