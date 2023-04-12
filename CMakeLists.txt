cmake_minimum_required(VERSION 3.22)
project(ultimate_py_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS} include)

if (WIN32)
    link_directories(
            # lib/win32/CL
            lib/win32/GL
            lib/win32/GLFW
    )

    # include_directories(share/cmake/OpenCL)
    # include_directories(share/cmake/OpenCLHeaders)
    # include_directories(share/cmake/OpenCLHeadersCpp)
    # include_directories(share/cmake/OpenCLICDLoader)
    # include_directories(share/cmake/nCLUtils)
    # include_directories(share/cmake/OpenCLUtilsCpp)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/DLLs/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
else ()
    message(SEND_ERROR "Currently only Windows is supported")
    return()
endif ()

set(LIBS
        ${OPENGL_LIBRARIES}

        glfw3
        glfw3dll

        # OpenCL
        # OpenCLUtils
        # OpenCLUtilsCpp
        # OpenCLUtilsCppd
        # OpenCLUtilsd

        glew32
        )

add_executable(
        ${PROJECT_NAME}

        src/utils/timer/Timer.cxx
        src/utils/logger/Logger.cxx

        src/core/render/components/mesh/presets/Plane.cxx
        src/core/render/components/mesh/presets/Sphere.cxx
        src/core/render/components/mesh/presets/Cube.cxx

        src/core/render/components/shaders/Shader.cxx
        src/core/render/components/shaders/ShaderProgram.cxx
        src/core/managers/sub_programs_managers/shader_manager/ShaderManager.cxx

        src/core/render/components/shaders/Shader.cxx
        src/core/render/components/shaders/ShaderProgram.cxx
        src/core/managers/sub_programs_managers/shader_manager/ShaderManager.cxx

        src/core/physics/solid/sphere/SolidSphere.cxx
        src/core/physics/solid/mesh/SolidMesh.cxx

        src/core/physics/Simulator.cxx
        src/core/physics/Collision.cxx

        src/core/physics/fluid/simple_fluid/CellsDistributor.cxx
        src/core/physics/fluid/simple_fluid/SimpleFluidContainer.cxx
        src/core/components/AbstractObject.cxx

        src/core/render/components/camera/Camera.cxx
        src/core/render/components/RenderObject.cxx
        src/core/render/Renderer.Main.cxx
        src/core/render/Renderer.Render.cxx

        src/core/managers/window_manager/WindowCompositor.cxx

        src/core/components/scene/PhysicalScene.cxx
        src/core/components/scene/RenderScene.cxx
        src/core/components/scene/Scene.cxx

        scenes/TestScene.cxx
        scenes/MeshScene.cxx
        #scenes/ClTestScene.cxx
        #scenes/GlTestScene.cxx
        #scenes/Control.cxx
        scenes/SceneLoader.cxx

        src/core/SceneCompositor.cxx
        src/core/Core.cxx
        src/main.cxx
)

message(${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/sub_programs/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/sub_programs/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/objects/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/objects/)
