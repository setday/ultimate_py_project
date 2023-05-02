/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Simulator.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "CollisionSolver.h"
#include "PhysicsSimulator.h"

using namespace unreal_fluid::physics;

void PhysicsSimulator::addPhysicalObject(IPhysicalObject *physicalObject) {
  if (physicalObject == nullptr) return;
  if (physicalObject->getType() == IPhysicalObject::Type::FLUID_CONTAINER_SIMPLE)
    dynamicObjects.push_back(physicalObject);
  else
    solidObjects.push_back(physicalObject);
}

void PhysicsSimulator::simulate(double dt) {
  if (timer.getStatus() == utils::Timer::State::PAUSED)
    return;

  for (auto &physObject: dynamicObjects)
    physObject->simulate(dt);

  for (auto &physObject: dynamicObjects) {
    for (auto &solidObject: solidObjects)
      interact(physObject, solidObject);
  }
}

void PhysicsSimulator::interact(IPhysicalObject *dynamicObject, IPhysicalObject *solid) {
  if (dynamicObject->getType() == IPhysicalObject::Type::FLUID_CONTAINER_SIMPLE
  || dynamicObject->getType() == IPhysicalObject::Type::FLUID_CONTAINER_ADVANCED) {
    auto particles = (std::vector<fluid::Particle *> *) dynamicObject->getData();
    if (solid->getType() == IPhysicalObject::Type::SOLID_SPHERE) {
      auto sphere = (solid::SolidSphere *) solid;
      for (auto &particle: *particles)
        CollisionSolver::particleWithSphereCollision(particle, sphere, 0.02);
    } else if (solid->getType() == IPhysicalObject::Type::SOLID_PLANE) {
      auto plane = (solid::Plane *) solid;
      for (auto &particle: *particles)
        CollisionSolver::particleWithPlaneCollision(particle, plane, 0.75);
    }
    //TODO for mesh
  }
}

// end of Simulator.cpp
