add_executable(Reporter Reporter.cpp)
target_include_directories(Reporter PRIVATE ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(Reporter PRIVATE common)