/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AbstractObject.h"
#include "../physics/solid/mesh/SolidMesh.h"
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/BasicMesh.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) :
  physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)) {}

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject) : physicalObject(physicalObject) {}

void AbstractObject::parse() {
  auto type = physicalObject->getType();
  void *data = physicalObject->getData();

  if (type == physics::IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER) {
    auto &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(data);

    for (int pos = 0; pos < particles.size(); ++pos) {
      if (pos >= renderObjects.size()) {
        renderObjects.push_back(new render::RenderObject {
          .mesh = render::mesh::Sphere(
                  (float) particles[pos]->radius,
                  int(particles[pos]->radius * 500),
                  int(particles[pos]->radius * 500)
          ),
          .material = render::material::MaterialFactory::createMaterial(render::material::MaterialFactory::MaterialType::GOLD),
        });
      }

      auto renderObject = renderObjects[pos];

      renderObject->position = particles[pos]->position;
      renderObject->modelMatrix = mat4::translation(renderObject->position);
    }

    return;
  }

  if (type == physics::IPhysicalObject::Type::SOLID_SPHERE) {
    auto solidSphere = *static_cast<physics::solid::SolidSphere *>(data);

    if (renderObjects.empty()) {
      renderObjects.push_back(new render::RenderObject {
        .mesh = render::mesh::Sphere((float) solidSphere.getRadius(), 50, 50),
        .material = render::material::MaterialFactory::createMaterial(render::material::MaterialFactory::MaterialType::BRONZE),
      });
    }

    auto renderObject = renderObjects.back();

    renderObject->position = solidSphere.getPosition();
    renderObject->modelMatrix = mat4::translation(renderObject->position);

    return;
  }

  if (type == physics::IPhysicalObject::Type::SOLID_MESH) {
    auto &triangles = *static_cast<std::vector<physics::solid::Triangle> *>(data);

    for (int pos = 0; pos < triangles.size(); ++pos) {
      auto const &triangle = triangles[pos];

      if (pos >= renderObjects.size()) {
        renderObjects.push_back(new render::RenderObject {
          .mesh = render::mesh::BasicMesh({triangle.v1, triangle.v2, triangle.v3}, {0, 1, 2}),
          .material = render::material::MaterialFactory::createMaterial(render::material::MaterialFactory::MaterialType::BRONZE),
        });
      }
    }

    return;
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}
