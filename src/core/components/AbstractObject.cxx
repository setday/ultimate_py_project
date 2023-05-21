/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 * PURPOSE   : Abstract object to store render and physical objects in one
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AbstractObject.h"
#include "../physics/gas/GasContainer2D.h"
#include "../physics/solid/mesh/SolidMesh.h"
#include "../render/components/mesh/presets/Cube.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject, const std::vector<render::RenderObject *> &renderObjects) : physicalObject(physicalObject),
                                                                                                                                     renderObjects(renderObjects) {}

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) : physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)) {}

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject) : physicalObject(physicalObject) {}

void parseGasContainer2d(physics::IPhysicalObject *container2D, std::vector<render::RenderObject *> &renderObjects) {
  void *data = container2D->getData();
  auto &cells = *static_cast<std::vector<std::vector<physics::gas::GasCell>> *>(data);

  size_t renderObjectPointer = 0;
  const float cubeSize = 0.03;

  for (size_t row = 0; row < cells.size(); ++row) {
    const auto &cellRow = cells[row];
    for (size_t col = 0; col < cellRow.size(); ++col) {
      const auto &cell = cellRow[col];

      if (renderObjectPointer >= renderObjects.size()) {
        auto renderObject = new render::RenderObject;
        renderObject->material = render::material::Debug();
        renderObject->material.diffuseColor = cell.color;
        renderObject->mesh = render::mesh::Cube(cubeSize);
        renderObject->modelMatrix = mat4::translation(vec3{float(col), float(row), 0} * cubeSize);
        renderObjects.push_back(renderObject);
      }

      renderObjects[renderObjectPointer]->material.diffuseColor = cell.color;
      renderObjects[renderObjectPointer++]->material.ambientColor = cell.pressure / 100.0;
    }
  }
}

void AbstractObject::parse() {
  auto type = physicalObject->getType();
  void *data = physicalObject->getData();

  switch (type) {
    using namespace physics;
    case IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER: {
      auto &particles = *static_cast<std::vector<fluid::Particle *> *>(data);

      for (size_t pos = 0; pos < particles.size(); ++pos) {

        if (pos >= renderObjects.size()) {

          auto renderObject = new render::RenderObject;

          renderObject->material = render::material::Gold();
          auto r = particles[pos]->radius;
          renderObject->mesh = render::mesh::Sphere(float(r), unsigned(500 * r), unsigned(500 * r));
          renderObjects.push_back(renderObject);
        }

        renderObjects[pos]
                ->modelMatrix = mat4::translation(particles[pos]->position);
      }
      break;
    }
    case IPhysicalObject::Type::SOLID_SPHERE: {
      auto solidSphere = *static_cast<solid::SolidSphere *>(data);

      if (renderObjects.empty()) {

        auto renderObject = new render::RenderObject;

        renderObject->material = render::material::Bronze();
        auto r = solidSphere.radius;
        renderObject->mesh = render::mesh::Sphere(float(r), unsigned(500 * r), unsigned(500 * r));
        renderObjects.push_back(renderObject);
      }

      renderObjects.back()
              ->modelMatrix = mat4::translation(solidSphere.position);
      break;
    }
    case IPhysicalObject::Type::SOLID_MESH: {

      auto &triangles = *static_cast<std::vector<solid::Triangle> *>(data);

      for (size_t pos = renderObjects.size(); pos < triangles.size(); ++pos) {
        const auto &triangle = triangles[pos];
        auto renderObject = new render::RenderObject;

        if (pos == 0)
          renderObject->material = render::material::Gold();
        else if (pos == 1)
          renderObject->material = render::material::RedPlastic();
        else
          renderObject->material = render::material::GreenPlastic();
        renderObject->mesh = render::mesh::BasicMesh({triangle.v1, triangle.v2, triangle.v3}, {0, 1, 2});
        renderObjects.push_back(renderObject);
      }
      break;
    }
    case IPhysicalObject::Type::SOLID_QUBE: {
      break;
    }
    case IPhysicalObject::Type::GAS_CONTAINER_2D: {
      parseGasContainer2d(physicalObject, renderObjects);
      break;
    }
    case IPhysicalObject::Type::DEFAULT: {
      break;
    }
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}

// end of AbstractObject.cxx
