cmake_minimum_required(VERSION 3.12)
project(mutex)

set(CMAKE_CXX_STANDARD 11)  

add_executable(mutex mutex.cpp)

find_package(Threads REQUIRED)
target_link_libraries(mutex PRIVATE Threads::Threads atomic)