cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)

project(ThreadPool)

add_executable(${PROJECT_NAME} main.cpp thread_pool.hpp thread_pool.inl
                               thread_pool.cpp)
