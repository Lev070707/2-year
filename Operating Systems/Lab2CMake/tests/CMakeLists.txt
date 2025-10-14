
cmake_minimum_required(VERSION 3.15)

find_package(Threads REQUIRED)

add_executable(thread_tests
  test_threads.cpp
)

target_include_directories(thread_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(thread_tests PRIVATE corelib Threads::Threads)

set_property(TARGET thread_tests PROPERTY CXX_STANDARD 17)
set_property(TARGET thread_tests PROPERTY CXX_STANDARD_REQUIRED ON)

add_test(NAME thread_tests COMMAND thread_tests)
