cmake_minimum_required(VERSION 3.20)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(primenumbers src/primenumbers.cpp)
target_include_directories(primenumbers PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE primenumbers)

enable_testing()
add_subdirectory(tests)