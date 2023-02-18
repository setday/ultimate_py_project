/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AbstractObject.h"

using namespace unreal_fluid;

void AbstractObject::update() {
//  physicsObject->update();
}

AbstractObject::~AbstractObject() {
  delete physicsObject;
  delete renderObject;
}

void AbstractObject::render() {
//  renderObject->render();
}
