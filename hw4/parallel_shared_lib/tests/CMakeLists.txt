cmake_minimum_required(VERSION 3.14)

add_executable(parallel_tests count.cpp)
target_include_directories(parallel_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(parallel_tests PRIVATE gtest_main ${PROJECT_NAME})

add_test(
    NAME parallel_test
    COMMAND valgrind
    "${PROJECT_SOURCE_DIR}/tests/parallel_tests"
    --leak-check=full
    --error-exitcode=1)
