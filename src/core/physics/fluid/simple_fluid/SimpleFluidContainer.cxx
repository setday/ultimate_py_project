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
#include "random"

using namespace unreal_fluid::physics::fluid;

SimpleFluidContainer::SimpleFluidContainer(FluidDescriptor descriptor) {
    k = 0.1;
    auto particle = new Particle();
    particle->position = {0.01, -0.01, -0.01};
    particle->mass = 1000000;
    particle->radius = 0.3;
    particles.push_back(particle);
    /*particle = new Particle();
    particle->position = {-0.5, 0, 0};
    particle->mass = 1;
    particle->radius = 0.3;
    particle->velocity = {1,0,0};
    particles.push_back(particle);*/
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
    for (int i = 0; i < particles.size(); ++i) {
        for (int j = i + 1; j < particles.size(); ++j) {
            if ((particles[i]->position - particles[j]->position).len() <= particles[i]->radius + particles[j]->radius){
                collide(particles[i], particles[j]);
            }
        }
    }
   /* CellsDistribution cells(particles);
    std::pair<Particle *, Particle *> p = cells.nextPair();
    while (p != CellsDistribution::terminator) {
        collide(p.first, p.second);
        p = cells.nextPair();
    }*/
}

void SimpleFluidContainer::simulate(double dt) {
    /// TODO addParticle() method should be used
    {
        for (int i = 0; i < 1; ++i) {
            double dX = 1.0*(rand() % 100)/100000;
            double dZ = 1.0*(rand() % 100)/100000;
            auto particle = new Particle;
            particle->position = {dX, 1, -dZ};
            particle->mass = 1;
            particle->radius = 0.02;
            particle->velocity = {0, -0.5, 0};
            particles.push_back(particle);
        }
    }
    interact(dt);
    //addExternalForces(dt);
    advect(dt);
}

void SimpleFluidContainer::collide(Particle *p1, Particle *p2) const {
    vec3 y = p2->position - p1->position;
    y.normalizeSelf();
    double push = (p1->radius + p2->radius - p1->position.distanceTo(p2->position)) / (p1->mass + p2->mass);
    p2->position += y * push * p1->mass;
    p1->position -= y * push * p2->mass;
    double s = -(1 + k) * (p1->velocity.project(y) - p2->velocity.project(y)) * p1->mass * p2->mass / (p1->mass + p2->mass);
    p1->velocity += y * (s / p1->mass);
    p2->velocity -= y * (s / p2->mass);
}

void *SimpleFluidContainer::getData() {
    return &particles;
}

unreal_fluid::physics::PhysicalObject::Type SimpleFluidContainer::getType() {
    return physics::PhysicalObject::Type::SIMPLE_FLUID_CONTAINER;
}

// end of FluidContainer.cxx
