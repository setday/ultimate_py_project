/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : FlagParser.cxx
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "FlagParser.h"

#include "./../../../../src/core/render/components/mesh/presets/Plane.h"

using namespace unreal_fluid::addons::physics;

void FlagParser::parse(const Flag &flag, render::RenderObject * &renderObject) {
  if (renderObject == nullptr) {
    render::mesh::Plane plane(1, 1, flag._widthSegments, flag._heightSegments);

    renderObject = new render::RenderObject {
      .bakedMesh = std::make_unique<render::mesh::BakedMesh>(&plane),
    };
  }

for (int i = 0; i < flag._widthSegments; ++i) {
    for (int j = 0; j < flag._heightSegments; ++j) {
      int index = i * flag._heightSegments + j;

      renderObject->bakedMesh->mesh->vertices[index].position = flag._points[index].position;
    }
  }
}

// end of FlagParser.cxx
