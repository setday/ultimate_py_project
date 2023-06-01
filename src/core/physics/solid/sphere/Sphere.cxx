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

#include "Sphere.h"

using namespace unreal_fluid::physics::solid;

Sphere::Sphere(vec3 position, double radius) : ISolid(position),
                                               radius(radius) {}

unreal_fluid::physics::IPhysicalObject::Type Sphere::getType() {
  return Type::SOLID_SPHERE;
}

void *Sphere::getData() {
  return this;
}

// end of SolidSphere.cxx
