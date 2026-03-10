include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE accumulate GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)