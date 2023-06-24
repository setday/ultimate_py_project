/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasContainer.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "GasContainer.h"

  using namespace unreal_fluid::physics::gas;

GasContainer::GasContainer(int height, int width, int depth) : _height(height), _width(width), _depth(depth) {
  _storage.resize(height);
  for (auto &i : _storage) {
    i.resize(width);
    for (auto &j : i) {
      j.resize(depth);
    }
  }

  for (int i = height * 1 / 6; i < height * 5 / 6; ++i) {
    for (int j = width * 1 / 6; j < width * 5 / 6; ++j) {
      for (int k = depth * 1 / 6; k < depth * 5 / 6; ++k) {
        _storage[i][j][k] = GasCell(100, {0.3, 0.3, 0.3}, 100);
      }
    }
  }
}

unreal_fluid::physics::IPhysicalObject::Type GasContainer::getType() {
  return Type::GAS_CONTAINER_3D;
}

void *GasContainer::getData() {
  return &_storage;
}

void GasContainer::simulate(double dt) {
  // pass
}

// end of GasContainer.cxx
