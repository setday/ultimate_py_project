/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AdvancedFluidContainer.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AdvancedFluidContainer.h"
#include <random>
#include "../../CollisionSolver.h"

unreal_fluid::physics::fluid::AdvancedFluidContainer::AdvancedFluidContainer(
        unreal_fluid::physics::fluid::FluidDescriptor descriptor) {
    interactionSolver = new helper::ClInteractionSolver(particles);
    addParticle({0, 0.5, 0}, {0,0,0}, 0.25, 1);
}

unreal_fluid::physics::fluid::AdvancedFluidContainer::~AdvancedFluidContainer() {
    delete interactionSolver;
    for (auto &particle: particles) {
        delete particle;
    }
}

unreal_fluid::physics::IPhysicalObject::Type unreal_fluid::physics::fluid::AdvancedFluidContainer::getType() {
    return Type::FLUID_CONTAINER_ADVANCED;
}

void *unreal_fluid::physics::fluid::AdvancedFluidContainer::getData() {
    return &particles;
}

void unreal_fluid::physics::fluid::AdvancedFluidContainer::simulate(double dt) {
    //flows();
    interact();
    addExternalForces(dt);
    advect(dt);
}

void unreal_fluid::physics::fluid::AdvancedFluidContainer::addParticle(vec3 position, vec3 velocity, double radius,
                                                                       double mass) {
    auto particle = new Particle;
    particle->position = position;
    particle->mass = mass;
    particle->radius = radius;
    particle->velocity = velocity;
    particles.push_back(particle);
}

void unreal_fluid::physics::fluid::AdvancedFluidContainer::flows() {
    for (int i = 0; i < 10; ++i) {
        addParticle({double(rand() % 100) / 100000, 1, double(rand() % 100) / 100000}, {0, 0, 0}, 0.01, 2);
    }
}

void unreal_fluid::physics::fluid::AdvancedFluidContainer::interact() {
    interactionSolver->interact();
}

void unreal_fluid::physics::fluid::AdvancedFluidContainer::addExternalForces(double dt) {
    for (auto &particle: particles) {
        particle->velocity += G * dt;
    }
}

void unreal_fluid::physics::fluid::AdvancedFluidContainer::advect(double dt) {
    for (auto particle: particles)
        particle->position += particle->velocity * dt;
}
