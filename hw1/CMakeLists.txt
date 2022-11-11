cmake_minimum_required(VERSION 3.10.0)
project(hw1)

option(BUILD_BIN "Enable building bin" ON)
option(BUILD_TESTS "Enable building tests" ON)
option(ENABLE_SANITIZERS "Enable sanitizers" OFF)
option(ENABLE_COVERAGE "Enable coverage" OFF)

set(C_CXX_WARNINGS "-Wall -Wpedantic -Wdeprecated -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_CXX_WARNINGS}")

add_subdirectory(lib)

if (BUILD_BIN)
    add_subdirectory(bin)
endif()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
