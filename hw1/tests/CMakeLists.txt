cmake_minimum_required(VERSION 3.10.0)
project(tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

file(GLOB tests "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.cpp")

message("abc")
enable_testing()
foreach(file ${tests})
  message(${file})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests" ${file} ${PROJECT_SOURCE_DIR}/main.cpp)
  target_link_libraries("${name}_tests" gtest_main gcov lib)
  add_test(NAME "${name}" COMMAND "${name}_tests")
endforeach()
