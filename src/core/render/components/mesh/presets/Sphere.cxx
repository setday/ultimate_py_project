/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Sphere.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Sphere.h"

using namespace unreal_fluid;
using namespace render::mesh;

Sphere::Sphere(float radius, unsigned int rings, unsigned int sectors) {
  float const dRings = 1.0f / (float) (rings - 1);
  float const dSectors = 1.0f / (float) (sectors - 1);

  for (unsigned int r = 0; r < rings; r++) {
    for (unsigned int s = 0; s < sectors; s++) {
      float const y = cos(math::PI * r * dRings);
      float const x = cos(2 * math::PI * s * dSectors) * sin(math::PI * r * dRings);
      float const z = sin(2 * math::PI * s * dSectors) * sin(math::PI * r * dRings);

      vertices.emplace_back(
              vec3f{x * radius, y * radius, z * radius},
              vec3f{x, y, z},
              vec2f{(float)s / (float)sectors, (float)r / (float)rings}
              );

      if (r != rings - 1 && s != sectors - 1) {
        indices.emplace_back(r * sectors + s);
        indices.emplace_back(r * sectors + (s + 1));
        indices.emplace_back((r + 1) * sectors + (s + 1));

        indices.emplace_back(r * sectors + s);
        indices.emplace_back((r + 1) * sectors + (s + 1));
        indices.emplace_back((r + 1) * sectors + s);
      }
    }
  }
}

// end of Sphere.cxx
