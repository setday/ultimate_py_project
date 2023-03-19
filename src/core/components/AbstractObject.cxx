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

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) {
  physObject = new physics::fluid::SimpleFluidContainer(descriptor);
  /// TODO: add nullptr check
}

void AbstractObject::parse() {
  physics::PhysObject::Type type = physObject->getType();
  auto data = physObject->getData();
  if (type == physics::PhysObject::Type::SIMPLE_FLUID_CONTAINER) {
    auto &particles = *reinterpret_cast<std::vector<physics::fluid::Particle *> *>(data);
    while (particles.size() > renderObjects.size()) {
      renderObjects.push_back(new render::RenderObject);
      renderObjects.back()->material = render::material::MaterialFactory::createMaterial(
              render::material::MaterialFactory::MaterialType::GOLD
      );
    }
    for (int i = 0; i < particles.size(); ++i) {
      auto &particle = particles[i];
      auto renderObject = renderObjects[i];
      renderObject->mesh = render::mesh::Sphere(particle->radius, 50, 50);
      //TODO Coordinates translator. vec3f move = {-.75f, 0.f, -5.f} is a nonsense
      vec3f move = {-.75f, 0.f, -5.f};
      renderObject->position = particle->position + move;
      renderObject->modelMatrix = mat4::translation(renderObject->position);
    }
  }
}

const std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

const physics::PhysObject *AbstractObject::getPhysObject() {
  return physObject;
}
