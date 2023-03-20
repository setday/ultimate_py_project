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
#include "../physics/fluid/Particle.h"
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) : physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)) {
  /// TODO add nullptr check
}

void AbstractObject::parse() {
  physics::PhysicalObject::Type type = physicalObject->getType();
  void *data = physicalObject->getData();
  if (type == physics::PhysicalObject::Type::SIMPLE_FLUID_CONTAINER) {
    std::vector<physics::fluid::Particle *> &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(data);
    for (int pos = 0; pos < particles.size(); ++pos) {
      if (pos >= renderObjects.size()) {
        renderObjects.push_back(new render::RenderObject);
        renderObjects.back()->material = render::material::MaterialFactory::createMaterial(
                render::material::MaterialFactory::MaterialType::GOLD
        );
      }
      auto &particle = particles[pos];
      auto &renderObject = renderObjects[pos];
      renderObject->mesh = render::mesh::Sphere((float) particle->radius, 10, 10);
      renderObject->position = particle->position;
      renderObject->modelMatrix = mat4::translation(renderObject->position);
    }
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::PhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}
