cmake_minimum_required(VERSION 3.16)
project(auto_win_msg)

set(CMAKE_CXX_STANDARD 23)

add_executable(auto_win_msg
               src/main.cpp
               src/windows.cpp
               src/Controller.cpp
               src/MouseLocator.cpp)
