add_executable(Creator Creator.cpp)
target_include_directories(Creator PRIVATE ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(Creator PRIVATE common)
