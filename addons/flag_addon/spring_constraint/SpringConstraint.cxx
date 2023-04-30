/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : SpringConstraint.cxx
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "SpringConstraint.h"

using namespace unreal_fluid::addons::physics;

void SpringConstraint::update() {
  vec3 position1 = body1->position;
  vec3 position2 = body2->position;

  vec3 velocity1 = body1->velocity;
  vec3 velocity2 = body2->velocity;

  vec3 positionDiff = position2 - position1;
  vec3 diffNormalized = positionDiff.normalized();

  float diffLength = positionDiff.len();

  vec3 force = diffNormalized * (diffLength - restLength) * stiffness;
  vec3 forceDamping = (velocity2 - velocity1) * damping;

  body1->applyForce(force - forceDamping, position1);
  body2->applyForce(-force + forceDamping, position2);
}

// end of SpringConstraint.cxx
