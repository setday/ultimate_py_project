#pragma once

#include <vector>

#include "../../../Definitions.h"
#include "meshes/BasicMesh.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    mesh::BasicMesh mesh;
    vec3f position = vec3f(0.0f, 0.0f, 0.0f);
    mat4 modelMatrix = mat4();

    float zAxisAngle = 0.0f;

    RenderObject() = default;
    ~RenderObject() = default;
  };
} // namespace unreal_fluid::render
