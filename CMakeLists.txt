cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "UDP-Debug-Reader")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/Input.cpp
        src/Input.hpp
        src/main.cpp
        src/network.cpp
        src/network.hpp)
