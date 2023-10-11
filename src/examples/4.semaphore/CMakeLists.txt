cmake_minimum_required(VERSION 3.12)
project(condition_variable)

set(CMAKE_CXX_STANDARD 20)  

add_executable(semaphore semaphore.cpp)

find_package(Threads REQUIRED)
target_link_libraries(semaphore PRIVATE Threads::Threads atomic)