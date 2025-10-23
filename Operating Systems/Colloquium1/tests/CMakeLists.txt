include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests test_utils.cpp)
target_link_libraries(tests PRIVATE utils gtest_main)

enable_testing()
add_test(NAME all_tests COMMAND tests)