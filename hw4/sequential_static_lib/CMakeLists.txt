cmake_minimum_required(VERSION 3.14)

project(sequential_static)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE src/count.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

add_subdirectory("./tests")

if (TEST_COVERAGE)
  target_link_libraries(${PROJECT_NAME} PRIVATE gcov)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage")
endif()
