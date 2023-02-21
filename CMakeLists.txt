cmake_minimum_required(VERSION 3.22)
project(ultimate_py_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS} include)

if (WIN32)
    link_directories(lib)
    include_directories(share/cmake/OpenCL)
    include_directories(share/cmake/OpenCLHeaders)
    include_directories(share/cmake/OpenCLHeadersCpp)
    include_directories(share/cmake/OpenCLICDLoader)
    include_directories(share/cmake/nCLUtils)
    include_directories(share/cmake/OpenCLUtilsCpp)
else ()
    message(SEND_ERROR "Currently only Windows is supported")
    return()
endif()

set(LIBS ${OPENGL_LIBRARIES} OpenCL OpenCLUtils OpenCLUtilsCpp OpenCLUtilsCppd OpenCLUtilsd)

add_executable(
        ${PROJECT_NAME}

        src/core/managers/sub_programs_managers/CLManager.cxx

        src/core/physics/PhysicsObject.cxx
        src/core/components/AbstractObject.cxx
        src/core/components/ObjectFactory.cxx

        src/core/render/components/RenderObject.cxx
        src/core/render/Renderer.cxx

        src/core/components/Scene.cxx
        scenes/CLTestScene.cxx

        src/core/Compositor.cxx
        src/core/Core.cxx
        src/main.cxx
        scenes/CLTestScene.cxx)

message(${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
