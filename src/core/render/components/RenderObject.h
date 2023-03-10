#pragma once

#include <vector>

#include "../../../Definitions.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<float>> colors;

    float zAxisAngle = 0.0f;

    RenderObject() = default;
    ~RenderObject() = default;
  };
} // namespace unreal_fluid::render
