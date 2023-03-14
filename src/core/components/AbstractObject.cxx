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

using namespace unreal_fluid;

void AbstractObject::parse() {
  physics::PhysObject::Type type = physObject->getType();
  auto data = physObject->getData();
  if (type == physics::PhysObject::Type::DEFAULT) {
    throw "Incomplete type parsing";
  } else if (type == physics::PhysObject::Type::FLUID1_CONTAINER) {
    auto &particles = *reinterpret_cast<std::vector<fluid::Particle *> *>(data);

    for (int pos = 0; pos < particles.size(); ++pos) {
      if (pos == renderObjects.size()) {
        auto sphere = new render::RenderObject;
        sphere->position = particles[pos]->c;
        sphere->modelMatrix = mat4::translation(sphere->position);
        renderObjects.push_back(sphere);
      } else {
        renderObjects[pos]->modelMatrix = mat4::translation(particles[pos]->c);
      }
    }
  }
}

void AbstractObject::update(double dt) {
  physObject->simulate(dt);
}

AbstractObject::~AbstractObject() {
}

void AbstractObject::render() {
  for (auto &renderObject : renderObjects) {
//    renderObject.;
  }
}
