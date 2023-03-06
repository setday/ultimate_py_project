/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#include "AbstractObject.h"

using namespace unreal_fluid;

void AbstractObject::Update() const {
//  physicsObject->update();
}

AbstractObject::~AbstractObject() {
  // delete physicsObject;
  delete _renderObject;
}

void AbstractObject::Render() const {
//  renderObject->render();
}
