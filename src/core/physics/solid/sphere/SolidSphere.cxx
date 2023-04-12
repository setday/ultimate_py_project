/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidSphere
 * PURPOSE   : solid class
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "SolidSphere.h"

using namespace unreal_fluid::physics::solid;

SolidSphere::SolidSphere(vec3 position, double radius) : position(position),
                                                         radius(radius) {}

unreal_fluid::physics::IPhysicalObject::Type SolidSphere::getType() {
  return physics::IPhysicalObject::Type::SOLID_SPHERE;
}

void *SolidSphere::getData() {
  return this;
}
