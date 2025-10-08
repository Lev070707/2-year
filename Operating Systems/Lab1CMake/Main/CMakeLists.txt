add_executable(Main Main.cpp)
target_include_directories(Main PRIVATE ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(Main PRIVATE common)