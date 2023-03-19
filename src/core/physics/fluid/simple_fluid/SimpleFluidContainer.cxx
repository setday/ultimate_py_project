/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : FluidContainer.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "SimpleFluidContainer.h"

using namespace unreal_fluid::physics::fluid;

SimpleFluidContainer::SimpleFluidContainer(FluidDescriptor descriptor) {
    k = 0.8;
    auto particle = new Particle();
    particle->position = {0, 0, 0};
    particle->mass = 1;
    particle->radius = 0.5;
    particle->velocity = {3, 0, 0};
    particles.push_back(particle);
    particle = new Particle();
    particle->position = {1.5, 0, 0};
    particle->mass = 1;
    particle->radius = 0.5;
    particles.push_back(particle);
    /// TODO : write constructor implementation
}

SimpleFluidContainer::~SimpleFluidContainer() {
    for (auto &particle: particles) {
        delete particle;
    }
}

void SimpleFluidContainer::addExternalForces(double dt) {
    for (auto &particle: particles) {
        particle->velocity += G * dt;
    }
}

void SimpleFluidContainer::advect(double dt) {
    for (auto particle: particles) {
        particle->position += particle->velocity * dt;
    }
}

void SimpleFluidContainer::interact(double dt) {
    /// TODO: repair CellsDistribution
    for (int i = 0; i < particles.size(); ++i) {
        for (int j = i + 1; j < particles.size(); ++j) {
            if ((particles[i]->position - particles[j]->position).len() <
                particles[i]->radius + particles[j]->radius) {
                collide(*particles[i], *particles[j]);
            }
        }
    }
    /*CellsDistribution cells(particles);
    std::pair<Particle *, Particle *> p = cells.nextPair(), end = {nullptr, nullptr};
    while (p != end) {
      collide(*p.first, *p.second);
      p = cells.nextPair();
    }*/
}

void SimpleFluidContainer::simulate(double dt) {
    {
        auto particle = new Particle();
        particle->position = {0, 0, 0};
        particle->mass = 1;
        particle->radius = 0.1;
        particle->velocity = {3, 0, 0};
        particles.push_back(particle);
    }/// TODO: addParticle() method should be used
    interact(dt);
    addExternalForces(dt);
    advect(dt);
}

void SimpleFluidContainer::collide(Particle &p1, Particle &p2) {
  vec3 positionDiff = p1.position - p2.position;

  if (positionDiff.len2() == 0)
    return;

  double distance = positionDiff.len();

  double pushValue = (p1.radius + p2.radius - distance) / 2;
  vec3 pushVector = positionDiff * pushValue / distance;

  p1.position += pushVector;
  p2.position -= pushVector;

  double frictionValue =
          -(1 + k) *
          (p1.velocity.project(positionDiff) - p2.velocity.project(positionDiff)) /
          (p1.mass + p2.mass);
  vec3 frictionVector = positionDiff * frictionValue / distance;

  p1.velocity += frictionVector * p1.mass;
  p2.velocity -= frictionVector * p2.mass;
}

void *SimpleFluidContainer::getData() {
    return &particles;
}

unreal_fluid::physics::PhysObject::Type SimpleFluidContainer::getType() {
    return physics::PhysObject::Type::SIMPLE_FLUID_CONTAINER;
}

// end of FluidContainer.cxx
