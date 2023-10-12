cmake_minimum_required(VERSION 3.12)
project(promise)

set(CMAKE_CXX_STANDARD 11)  

add_executable(promise promise.cpp)

find_package(Threads REQUIRED)
target_link_libraries(promise PRIVATE Threads::Threads atomic)