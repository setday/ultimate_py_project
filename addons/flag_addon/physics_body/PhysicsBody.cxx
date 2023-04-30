/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : PhysicsBody.h
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "PhysicsBody.h"

using namespace unreal_fluid::addons::physics;

void PhysicsBody::applyForce(const vec3 &force, const vec3 &point) {
  angularAcceleration += vec3::cross(point - position, force);
  acceleration += force * inverseMass;
}

void PhysicsBody::applyImpulse(const vec3 &impulse, const vec3 &point) {
  angularVelocity += vec3::cross(point - position, impulse);
  velocity += impulse * inverseMass;
}

void PhysicsBody::applyTorque(const vec3 &torque) {
  angularAcceleration += torque;
}

void PhysicsBody::applyAngularImpulse(const vec3 &angularImpulse) {
  angularVelocity += angularImpulse;
}

void PhysicsBody::update(double dt) {
  if (isStatic) {
    return;
  }

  velocity += acceleration * dt;
  position += velocity * dt;
  acceleration = {0.0f, 0.0f, 0.0f};

  angularVelocity += angularAcceleration * dt;
  rotation += angularVelocity * dt;
  angularAcceleration = {0.0f, 0.0f, 0.0f};
}

// end of PhysicsBody.cxx
