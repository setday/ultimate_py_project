cmake_minimum_required(VERSION 3.24)
project(ultimate_py_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        ultimate_py_project

        src/core/render/components/Object.cxx
        src/core/render/components/Scene.cxx
        src/core/Compositor.cxx
        src/core/Core.cxx
        src/main.cxx
)