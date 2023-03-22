/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.h
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "CollisionPairs.h."
#include "CollisionPairs.h"


void unreal_fluid::physics::fluid::CollisionPairs::particleAndParticle(Particle *p1, Particle *p2, double k) {
    vec3 y = p2->position - p1->position;
    y.normalizeSelf();
    double push = (p1->radius + p2->radius - p1->position.distanceTo(p2->position)) / 2;
    p2->position += y * push;
    p1->position -= y * push;
    double s = -(1 + k) * (p1->velocity.project(y) - p2->velocity.project(y)) * p1->mass * p2->mass /
               (p1->mass + p2->mass);
    p1->velocity += y * (s / p1->mass);
    p2->velocity -= y * (s / p2->mass);
}

void unreal_fluid::physics::fluid::CollisionPairs::particleAndSolidSphere(Particle *p, solid::SolidSphere *s, double k) {
    vec3 y = s->getPosition() - p->position;
    y.normalizeSelf();
    vec3 spherePosition = s->getPosition();
    double push = s->getRadius() + p->radius - p->position.distanceTo(spherePosition);
    p->position -= y * push;
    p->velocity -= y * (1 + k) * p->velocity.project(y);
}
