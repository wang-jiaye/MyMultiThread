cmake_minimum_required(VERSION 3.12)
project(thread)

set(CMAKE_CXX_STANDARD 11)

add_executable(thread thread.cpp)

find_package(Threads REQUIRED)
target_link_libraries(thread PRIVATE Threads::Threads)