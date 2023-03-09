#pragma once

#include <vector>

#include "mesh/BasicMesh.h"
#include "material/BaseMaterial.h"
#include "shaders/ShaderProgram.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    mesh::BasicMesh mesh;
    material::BaseMaterial material;
    const ShaderProgram *shaderProgram = nullptr;

    mat4 modelMatrix = mat4();

    // Legacy
    vec3f position = vec3f(0.0f, 0.0f, 0.0f);
    float zAxisAngle = 0.0f;

    RenderObject() = default;
    ~RenderObject() = default;
  };
} // namespace unreal_fluid::render
