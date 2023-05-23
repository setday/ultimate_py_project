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

GasCell::GasCell(int particleCount) : particleCount(particleCount) {}

double GasCell::getPressure() const { return particleCount * temperature / volume; }

GasContainer2d::GasContainer2d(int height, int width, int particle_number) : height(height),
                                                                             width(width),
                                                                             storage(height) {
  for (auto &row: storage) row.resize(width);
  for (int counter = 0; counter < particle_number; ++counter) {
    int x = rand() % (height / 3 + 1), y = rand() % (width / 3 + 1);
    storage[x][y] = GasCell(rand() % 10 + 3);
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
  double meanPressure = (cell1.getPressure() + cell2.getPressure() + cell3.getPressure() + cell4.getPressure()) / 4;
  double pressureDiff = (cell.getPressure() - meanPressure) / 10;
  double forthDiff = abs(pressureDiff) / 4;
  if (pressureDiff > 0) { // давление в клетке больше, чем в соседях
    slice(cell, pressureDiff);
    add(cell1, forthDiff);
    add(cell2, forthDiff);
    add(cell3, forthDiff);
    add(cell4, forthDiff);
  } else {
    add(cell, -pressureDiff);
    slice(cell1, forthDiff);
    slice(cell2, forthDiff);
    slice(cell3, forthDiff);
    slice(cell4, forthDiff);
  }
}

void GasContainer2d::slice(GasCell &cell, double pressure) {
  cell.particleCount = cell.getPressure() / pressure;
}

void GasContainer2d::add(GasCell &cell, double pressure) {
  cell.particleCount *= pressure / cell.getPressure();
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
