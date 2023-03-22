/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.cxx
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "SimpleFluidContainer.h"
#include "CollisionPairs.h"
#include "random"

using namespace unreal_fluid::physics::fluid;

SimpleFluidContainer::SimpleFluidContainer(FluidDescriptor descriptor) {
    k = 0.1;
    //addParticle({0.01, -0.01, -0.01}, {0, 0, 0}, 0.3, 1000000);
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

void SimpleFluidContainer::interact() {
    /*for (int i = 0; i < particles.size(); ++i) {
        for (int j = i + 1; j < particles.size(); ++j) {
            if ((particles[i]->position - particles[j]->position).len() <
                particles[i]->radius + particles[j]->radius) {
                collide(particles[i], particles[j]);
            }
        }
    }*/
    CellsDistributor cells(particles);
    for (auto bigParticle: cells.getBigParticles()) {
      for (auto particle: particles) {
        if (particle->position != bigParticle->position && (particle->position - bigParticle->position).len() <= particle->radius + bigParticle->radius)
          collide(particle, bigParticle);
      }
    }
    std::pair<Particle *, Particle *> p = cells.nextPair();
    while (p != CellsDistributor::terminator) {
      if ((p.first->position - p.second->position).len() <= p.first->radius + p.second->radius)
        collide(p.first, p.second);
      p = cells.nextPair();
    }
}

void SimpleFluidContainer::simulate(double dt) {
    for (int i = 0; i < 10; ++i) {
        addParticle({double(rand() % 100) / 100000, 1, double(rand() % 100) / 100000}, {0, -0.5, 0}, 0.02, 1);
        //addParticle({1, double(rand() % 100) / 100000, double(rand() % 100) / 100000}, {-0.5, 0, 0}, 0.03, 2);
    }
    interact();
    addExternalForces(dt);
    advect(dt);
}

void SimpleFluidContainer::collide(Particle *p1, Particle *p2) const {
    CollisionPairs::particleAndParticle(p1, p2, k);
}

void *SimpleFluidContainer::getData() {
    return &particles;
}

unreal_fluid::physics::IPhysicalObject::Type SimpleFluidContainer::getType() {
    return physics::IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER;
}

void SimpleFluidContainer::addParticle(vec3 position, vec3 velocity, double radius, double mass) {
    auto particle = new Particle;
    particle->position = position;
    particle->mass = mass;
    particle->radius = radius;
    particle->velocity = velocity;
    particles.push_back(particle);
}

void SimpleFluidContainer::interact(unreal_fluid::physics::solid::ISolid *solid) {
    if (solid->getType() == Type::SOLID_SPHERE) {
        collideWithSolidSphere((solid::SolidSphere *) solid);
    }
}

void SimpleFluidContainer::collideWithSolidSphere(unreal_fluid::physics::solid::SolidSphere *sphere) {
    for (auto &particle: particles) {
        if ((particle->position - sphere->getPosition()).len() <= particle->radius + sphere->getRadius()) {
            CollisionPairs::particleAndSolidSphere(particle, sphere, k);
        }
    }
}

// end of FluidContainer.cxx
