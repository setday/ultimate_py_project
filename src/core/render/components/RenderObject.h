#pragma once

#include <vector>

#include "mesh/BasicMesh.h"
#include "material/BaseMaterial.h"
#include "../../managers/sub_programs_managers/shader_manager/ShaderManager.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    mesh::BasicMesh mesh;
    material::BaseMaterial material;
    const ShaderProgram *shaderProgram = render::DefaultShaderManager::GetDefaultProgram();

    mat4 modelMatrix = mat4();

    [[deprecated("It is strongly recommended to use modelMatrix instead of position")]]
    vec3f position = vec3f(0.0f, 0.0f, 0.0f);
    [[deprecated("It is strongly recommended to use modelMatrix instead of zAxisAngle")]]
    float zAxisAngle = 0.0f;

    RenderObject() = default;
    ~RenderObject() = default;
  };
} // namespace unreal_fluid::render
