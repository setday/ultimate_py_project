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

GasCell::GasCell(int pressure, int color) : pressure(pressure),
                                            color(color) {}

GasContainer2d::GasContainer2d(int height, int width, int particle_number) : height(height),
                                                                             width(width),
                                                                             storage(height) {
  for (auto &row: storage) row.resize(width);

  for (int counter = 0; counter < particle_number; ++counter) {
    int x = rand() % height, y = rand() % width;
    storage[x][y] = GasCell(100, 1);
  }
}

void GasContainer2d::simulationStage(double dt) {
  for (size_t row = 0; row < height; ++row) {
    for (size_t column = 0; column < width; ++column) {
      if (row != height - 1)
        simulate(storage[row][column], storage[row + 1][column], dt);
      if (column != width - 1)
        simulate(storage[row][column], storage[row][column + 1], dt);
    }
  }
}

void GasContainer2d::simulate(GasCell &cell1, GasCell &cell2, double dt) {
  double pressureDiff = (cell1.pressure - cell2.pressure) / 100;
  if (pressureDiff > 0) { // давление в первой клетке больше, чем во второй
    slice(cell1, pressureDiff);
    add(cell2, pressureDiff);
  } else {
    slice(cell2, pressureDiff);
    add(cell1, pressureDiff);
  }
}

void GasContainer2d::slice(GasCell &cell, double pressure) {
  double percentage = pressure / cell.pressure;
  cell.color /= percentage;
  cell.pressure -= pressure;
}

void GasContainer2d::add(GasCell &cell, double pressure) {
  double percentage = pressure / cell.pressure;
  cell.color *= percentage;
  cell.pressure += pressure;
}

void GasContainer2d::parse() {
  for (int pos = 0; pos < storage.size(); ++pos) {
    for (int posy = 0; posy < storage[pos].size(); ++posy) {
      /// TODO parse cells to render them. I'm not sure how, why and when.
    }
  }
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
