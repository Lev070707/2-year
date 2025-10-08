add_library(common STATIC
    employee.h
    fileops.h
    fileops.cpp
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})




