include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests/main.cpp")

foreach(file ${tests})
  message(${file})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests" ${file} ${PROJECT_SOURCE_DIR}/tests/main.cpp)
  target_link_libraries("${name}_tests" gtest_main hw2)
  add_test(NAME "${name}" COMMAND "${name}_tests")
endforeach()
