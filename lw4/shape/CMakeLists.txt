cmake_minimum_required(VERSION 3.15)
set(CURRENT_TASK_NAME "shape")
project(${CURRENT_TASK_NAME})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.h
)
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main\\.cpp$")
add_executable("${CURRENT_TASK_NAME}" ${PROJECT_SOURCES} src/main.cpp)
add_executable("${CURRENT_TASK_NAME}_tests" ${PROJECT_SOURCES} tests/tests.cpp)
target_include_directories(${CURRENT_TASK_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${CURRENT_TASK_NAME}_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries("${CURRENT_TASK_NAME}_tests" PRIVATE GTest::gtest GTest::gtest_main GTest::gmock)
target_link_libraries("${CURRENT_TASK_NAME}" PRIVATE SFML::Graphics)

enable_testing()
include(GoogleTest)
gtest_discover_tests("${CURRENT_TASK_NAME}_tests")



