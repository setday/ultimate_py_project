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
#include "../physics/solid/sphere/SolidSphere.h"
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor, const compositor::Compositor *compositor) : physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)),
                                                                                                                       compositor(compositor) {
}

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject, const compositor::Compositor *compositor) : physicalObject(physicalObject),
                                                                                                                     compositor(compositor) {
}

void AbstractObject::parse() {
  physics::IPhysicalObject::Type type = physicalObject->getType();
  void *data = physicalObject->getData();
  if (type == physics::IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER) {
    auto &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(data);
    for (int pos = 0; pos < particles.size(); ++pos) {
      if (pos >= renderObjects.size()) {
        auto renderObject = new render::RenderObject;
        renderObject->material = render::material::MaterialFactory::createMaterial(render::material::MaterialFactory::MaterialType::GOLD);
        renderObject->mesh = render::mesh::Sphere((float) particles[pos]->radius, int(particles[pos]->radius * 500), int(particles[pos]->radius * 500));
        /// TODO check if this dynamic quality is correct
        renderObjects.push_back(renderObject);
      }
      auto &particle = particles[pos];
      auto &renderObject = renderObjects[pos];
      renderObject->position = particle->position;
      renderObject->modelMatrix = mat4::translation(renderObject->position);
    }
  } else if (type == physics::IPhysicalObject::Type::SOLID_SPHERE) {
    auto solidSphere = reinterpret_cast<physics::solid::SolidSphere *>(data);
    if (renderObjects.empty()) {
      auto renderObject = new render::RenderObject;
      renderObject->material = render::material::MaterialFactory::createMaterial(render::material::MaterialFactory::MaterialType::GREEN_PLASTIC);
      renderObject->mesh = render::mesh::Sphere((float) solidSphere->getRadius(), 50, 50);
      renderObjects.emplace_back(renderObject);
    }
    renderObjects.back()->position = solidSphere->getPosition();
    renderObjects.back()->modelMatrix = mat4::translation(renderObjects[0]->position);
  } else if (type == physics::IPhysicalObject::Type::SOLID_MESH) {
    Logger::logInfo("Mesh");
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}
