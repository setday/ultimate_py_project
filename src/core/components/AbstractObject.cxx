/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 * PURPOSE   : Abstract object to store render and physical objects in one
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "AbstractObject.h"
#include "Parser.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject, const std::vector<render::RenderObject *> &renderObjects) : physicalObject(physicalObject),
                                                                                                                                     renderObjects(renderObjects) {}

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) : physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)) {}

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject) : physicalObject(physicalObject) {}

void AbstractObject::parse() {
  if (physicalObject == nullptr) return;
  auto type = physicalObject->getType();

  switch (type) {
    using namespace physics;
    case IPhysicalObject::Type::FLUID_CONTAINER_SIMPLE:
      Parser::parseContainer(*physicalObject, renderObjects);
      break;
    case IPhysicalObject::Type::FLUID_CONTAINER_ADVANCED:
      Parser::parseContainer(*physicalObject, renderObjects);
      break;
    case IPhysicalObject::Type::SOLID_MESH:
      Parser::parseMesh(*physicalObject, renderObjects);
      break;
    case IPhysicalObject::Type::SOLID_SPHERE:
      Parser::parseSphere(*physicalObject, renderObjects);
      break;
    case IPhysicalObject::Type::SOLID_PLANE:
      Parser::parsePlane(*physicalObject, renderObjects);
      break;
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}

// end of AbstractObject.cxx
