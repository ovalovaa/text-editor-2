cmake_minimum_required(VERSION 3.31)
project(untitled6)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled6 main.cpp
        Clipboard.cpp
        Clipboard.h
        History.cpp
        History.h
        Constants.h
        TextEditor.cpp
        TextEditor.h)
