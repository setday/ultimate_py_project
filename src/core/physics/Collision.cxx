/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Collision.cxx
 * PURPOSE   : Implements collision between different objects
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Collision.h"

using namespace unreal_fluid::physics;

void Collision::particlesCollision(fluid::Particle *p1, fluid::Particle *p2, double k) {
  vec3 diff = p1->position - p2->position;

  if (diff.len2() == 0) return;

  vec3 direction = diff.normalize();

  double pushValue =
          (p1->radius + p2->radius - diff.len()) /
          (p1->mass + p2->mass);

  if (pushValue < 0) return;

  vec3 pushVector = direction * pushValue;

  p1->position += pushVector * p2->mass;
  p2->position -= pushVector * p1->mass;

  double momentumValue =
          (1 + k) *
          (p1->velocity.dot(direction) - p2->velocity.dot(direction)) /
          (p1->mass + p2->mass);
  vec3 momentum = direction * momentumValue;

  p1->velocity -= momentum * p2->mass;
  p2->velocity += momentum * p1->mass;
}

void Collision::sphereCollision(fluid::Particle *p, solid::SolidSphere *s, double k) {
  vec3 y = s->getPosition() - p->position;
  y.normalizeSelf();
  vec3 spherePosition = s->getPosition();
  double push = s->getRadius() + p->radius - p->position.distanceTo(spherePosition);
  p->position -= y * push;
  p->velocity -= y * (1 + k) * p->velocity.project(y);
}
