cmake_minimum_required(VERSION 3.12)
project(procon)

set(CMAKE_CXX_STANDARD 11)  

add_executable(procon main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(procon PRIVATE Threads::Threads atomic)