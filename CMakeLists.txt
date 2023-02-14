cmake_minimum_required(VERSION 3.24)
project(ultimate_py_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        ultimate_py_project

        src/core/Core.cxx
        src/main.cxx
        )
