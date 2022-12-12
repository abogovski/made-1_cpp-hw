cmake_minimum_required(VERSION 3.14)

add_executable(sequential_tests count.cpp)
target_include_directories(sequential_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(sequential_tests PRIVATE gtest_main ${PROJECT_NAME})

add_test(
    NAME sequential_test
    COMMAND valgrind
    "${PROJECT_SOURCE_DIR}/tests/sequential_tests"
    --leak-check=full
    --error-exitcode=1)
