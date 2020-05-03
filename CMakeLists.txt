cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "UDP-Debug-Logger")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        source/Input.cpp
        source/Input.hpp
        source/main.cpp
        source/network.cpp
        source/network.hpp)
