cmake_minimum_required(VERSION 3.10.0)
project(lib)

file(GLOB LIB_SRCS "${PROJECT_SOURCE_DIR}/*.c")

add_library(lib ${LIB_SRCS})
target_include_directories(lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

if (ENABLE_COVERAGE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
endif()
if (NOT ENABLE_COVERAGE AND NOT ENABLE_SANTIZERS)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()
