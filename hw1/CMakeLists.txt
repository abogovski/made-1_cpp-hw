cmake_minimum_required(VERSION 3.10.0)
project(hw1)

option(BUILD_BIN "Enable building bin" ON)
option(BUILD_TESTS "Enable building tests" ON)

add_subdirectory(lib)

if (BUILD_BIN)
    add_subdirectory(bin)
endif()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
