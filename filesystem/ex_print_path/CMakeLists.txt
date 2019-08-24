cmake_minimum_required(VERSION 3.5)
PROJECT(filesystem_test LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS NO
)
target_link_libraries(${PROJECT_NAME} stdc++fs)

