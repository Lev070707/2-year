include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests.cpp
)

target_link_libraries(tests
    PRIVATE
    gtest_main
    common
)

enable_testing()
add_test(NAME AllTests COMMAND tests)
