add_library(utils STATIC utils.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Main Colloquium.cpp)
target_link_libraries(Main PRIVATE utils)
