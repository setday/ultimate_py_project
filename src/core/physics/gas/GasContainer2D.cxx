/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasContainer2D.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "GasContainer2D.h"

using namespace unreal_fluid::physics::gas;

GasCell::GasCell(double pressure, vec3f color) : pressure(pressure),
                                                 color(color) {}

GasContainer2d::GasContainer2d(int height, int width, int particle_number) : height(height),
                                                                             width(width),
                                                                             storage(height) {
  for (auto &row: storage) row.resize(width);

  for (int counter = 0; counter < particle_number; ++counter) {
    int x = rand() % (height / 3 + 1), y = rand() % (width / 3 + 1);
    storage[x][y] = GasCell(rand() % 5 + 2);
  }
}

void GasContainer2d::simulationStage(double dt) {
  for (size_t row = 1; row < height - 1; ++row) {
    for (size_t column = 1; column < width - 1; ++column) {
      simulate(storage[row][column], storage[row + 1][column], storage[row - 1][column], storage[row][column - 1], storage[row][column + 1], dt);
    }
  }
}

void GasContainer2d::simulate(GasCell &cell, GasCell &cell1, GasCell &cell2, GasCell &cell3, GasCell &cell4, double dt) {
  double meanPressure = (cell1.pressure + cell2.pressure + cell3.pressure + cell4.pressure) / 4;
  double pressureDiff = (cell.pressure - meanPressure) / 20;
  if (pressureDiff > 0) { // давление в клетке больше, чем в соседях
    slice(cell, pressureDiff);
    add(cell1, pressureDiff);
    add(cell2, pressureDiff);
    add(cell3, pressureDiff);
    add(cell4, pressureDiff);
  } else {
    add(cell, pressureDiff);
    slice(cell1, pressureDiff);
    slice(cell2, pressureDiff);
    slice(cell3, pressureDiff);
    slice(cell4, pressureDiff);
  }
}

void GasContainer2d::slice(GasCell &cell, double pressure) {
  cell.color *= cell.pressure / pressure;
  cell.pressure -= pressure;
}

void GasContainer2d::add(GasCell &cell, double pressure) {
  cell.color *= pressure / cell.pressure;
  cell.pressure += pressure;
}

unreal_fluid::physics::IPhysicalObject::Type GasContainer2d::getType() {
  return Type::GAS_CONTAINER_2D;
}

void *GasContainer2d::getData() {
  return &storage;
}

void GasContainer2d::simulate(double dt) {
  simulationStage(dt);
}
