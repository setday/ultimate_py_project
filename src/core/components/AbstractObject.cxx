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

AbstractObject::AbstractObject() {
  physObject = new physics::PhysObject;
}

AbstractObject::~AbstractObject() {
  delete physObject;
}

void AbstractObject::parse() {
  physics::PhysObject::Type type = physObject->getType();
  auto data = physObject->getData();
  if (type == physics::PhysObject::Type::DEFAULT) {
    throw "Incomplete type parsing";
  } else if (type == physics::PhysObject::Type::FLUID1_CONTAINER) {
    auto &particles = *reinterpret_cast<std::vector<physics::fluid::Particle *> *>(data);

    for (int pos = 0; pos < particles.size(); ++pos) {
      if (pos == renderObjects.size()) {
        auto sphere = new render::RenderObject;
        sphere->position = particles[pos]->coords;
        sphere->modelMatrix = mat4::translation(sphere->position);
        renderObjects.push_back(sphere);
      } else {
        renderObjects[pos]->modelMatrix = mat4::translation(particles[pos]->coords);
      }
    }
  }
}

void AbstractObject::update(double dt) {
  if (physObject == nullptr) {
    std::cout << "Can't simulate empty object\n";
    return;
  }
  physObject->simulate(dt);
  parse(); // does this look ok?
}

void AbstractObject::render() {
  for (auto &renderObject: renderObjects) {
    //    renderObject.render(); /// TODO: no render method in renderObject? I don't understand.
  }
}