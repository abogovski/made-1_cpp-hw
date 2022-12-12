cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)
FetchContent_MakeAvailable(googletest)

project(hw4)

enable_testing()
option(TEST_COVERAGE "Compile for test coverage measurements" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wpedantic")

add_subdirectory("${PROJECT_SOURCE_DIR}/sequential_static_lib")
add_subdirectory("${PROJECT_SOURCE_DIR}/parallel_shared_lib")

add_executable(count_sequential main.cpp)
target_compile_definitions(count_sequential PRIVATE PARALLEL=0)
target_link_libraries(count_sequential PRIVATE sequential_static)

add_executable(count_parallel main.cpp)
target_compile_definitions(count_parallel PRIVATE PARALLEL=1)
target_link_libraries(count_parallel PRIVATE parallel_shared)
