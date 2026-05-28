cmake_minimum_required(VERSION 3.15)
set(CURRENT_TASK_NAME "vehicle")

project(${CURRENT_TASK_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.h
)
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main\\.cpp$")
add_executable("${CURRENT_TASK_NAME}" ${PROJECT_SOURCES} src/main.cpp)
add_executable("${CURRENT_TASK_NAME}_tests" ${PROJECT_SOURCES} tests/tests.cpp)
set(PROJECT_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/IPeople
        ${CMAKE_CURRENT_SOURCE_DIR}/src/IVehicles
        ${CMAKE_CURRENT_SOURCE_DIR}/src/People
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Vehicles
)
target_include_directories(${CURRENT_TASK_NAME} PRIVATE ${PROJECT_INCLUDE_DIRS})
target_include_directories(${CURRENT_TASK_NAME}_tests PRIVATE ${PROJECT_INCLUDE_DIRS})
target_link_libraries("${CURRENT_TASK_NAME}_tests" PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests("${CURRENT_TASK_NAME}_tests")
