/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Plane.cxx
 * PURPOSE   : class to create planes for bounding box
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Plane.h"

using namespace unreal_fluid::physics::solid;

Plane::Plane(double height, double width, vec3 position, vec3 normal, vec3 right) : ISolid(position),
                                                                                    width(width),
                                                                                    height(height) {
  this->normal = normal.normalize();
  front = normal.cross(right);
  front.normalizeSelf();
  this->right = normal.cross(front);
}

unreal_fluid::physics::IPhysicalObject::Type Plane::getType() {
  return IPhysicalObject::Type::SOLID_PLANE;
}

void *Plane::getData() {
  return this;
}
