/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Plane.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Plane.h"

using namespace unreal_fluid::render::mesh;

Plane::Plane(float width, float height, unsigned int widthSegments, unsigned int heightSegments, vec3f forward, vec3f right) {
  vec3f up = forward.cross(right);

  float widthStep = width / widthSegments;
  float heightStep = height / heightSegments;

  for (unsigned int i = 0; i <= heightSegments; ++i) {
    for (unsigned int j = 0; j <= widthSegments; ++j) {
      float x = j * widthStep - width / 2;
      float y = i * heightStep - height / 2;

      vec3f position = x * right + y * forward;
      vec3f normal = up;
      vec2f texCoord = {(float) i / widthSegments, (float) j / heightSegments};


      vertices.emplace_back(position, normal, texCoord);
    }
  }

  /* Front side */

  for (unsigned int i = 0; i < heightSegments; ++i) {
    for (unsigned int j = 0; j <= widthSegments; ++j) {
      unsigned int first = i * (widthSegments + 1) + j;
      unsigned int second = first + widthSegments + 1;

      indices.push_back(first);
      indices.push_back(second);
    }

    indices.push_back(RESET_INDEX);
  }

  /* Back side */

  for (unsigned int i = 0; i < heightSegments; ++i) {
    for (unsigned int j = 0; j <= widthSegments; ++j) {
      unsigned int first = i * (widthSegments + 1) + j;
      unsigned int second = first + widthSegments + 1;

      indices.push_back(second);
      indices.push_back(first);
    }

    indices.push_back(RESET_INDEX);
  }

  meshType = 1;
}

// end of Plane.cxx
