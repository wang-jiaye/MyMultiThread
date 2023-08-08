cmake_minimum_required(VERSION 3.12)
project(condition_variable)

set(CMAKE_CXX_STANDARD 11)  

add_executable(condition_variable condition_variable.cpp)

find_package(Threads REQUIRED)
target_link_libraries(condition_variable PRIVATE Threads::Threads atomic)