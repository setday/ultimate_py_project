/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : UnrealFluidPhysics
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : Line2D.h
* PURPOSE   :
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#pragma once

#define LINE2D_NULL_POINT vec3f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), 0)
#include "../logger/Logger.h"
#include "MathHeaders"
#include <climits>

namespace unreal_fluid::math {
  class Line2D {
  private:
    constexpr static const float ACCURACY = 1e-6;
    float k, m;
    float a, b, c, length;
    vec3 p1, p2;

  public:
    Line2D(vec2 p1, vec2 p2);
    ~Line2D() = default;
    vec3f intersectSegmentWithSegment(Line2D l);
    vec3f intersectLineWithLine(Line2D l);
    vec3f intersectSegmentWithLine(Line2D l);
    float distanceLineToPoint(vec3f p) const;
    float distanceSegmentToPoint(vec3f p);
  };
} // namespace unreal_fluid::math