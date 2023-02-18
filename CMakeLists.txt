cmake_minimum_required(VERSION 3.24)
project(ultimate_py_project)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(
        ${PROJECT_NAME}

        src/core/render/window_manager/WindowCompositor.cxx

        src/core/render/components/RenderObject.cxx
        src/core/render/components/Scene.cxx

        src/core/render/Renderer.cxx

        src/core/Compositor.cxx

        src/core/Core.cxx
        src/main.cxx
)

target_include_directories(
        ${PROJECT_NAME}

        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes/glfw/include
)
target_link_libraries(
        ${PROJECT_NAME}

        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes/opengl/opengl32.dll
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes/opengl/glu32.dll
)
