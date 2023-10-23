cmake_minimum_required(VERSION 3.14)
project(runtest)

set(CMAKE_CXX_STANDARD 11)
enable_testing()

add_subdirectory(../3rdparty/googletest-1.14.0 googletest)


add_executable(runtest mutextest.cpp)
target_link_libraries(runtest gtest gtest_main)
