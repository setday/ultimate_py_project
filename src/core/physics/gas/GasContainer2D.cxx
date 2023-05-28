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

GasCell::GasCell(double amountOfGas, vec3f color, double temperature) : amountOfGas(amountOfGas),
                                                                        color(color),
                                                                        temperature(temperature) {}

GasContainer2d::GasContainer2d(int height, int width, int particle_number) : height(height),
                                                                             width(width) {
  storage.resize(height, std::vector<GasCell>(width));
  temporary.resize(height, std::vector<GasCell>(width));

  for (int counter = 0; counter < particle_number; ++counter) {
    int x = rand() % height, y = rand() % width;
    storage[x][y] = GasCell(rand() % 100, vec3f(rand() % 2, rand() % 2, rand() % 2));
  }
}

double GasCell::getPressure() const {
  const double gasConstant = 0.003; // real = 8.3144598
  return amountOfGas * gasConstant * temperature / volume;
}

double calculateFlow(GasCell &cell1, GasCell &cell2) {
  double pressureDiff = cell1.getPressure() - cell2.getPressure();
  double targetFlow = pressureDiff / 10.0;
  return targetFlow;
}

void GasContainer2d::increase(GasCell &cell1, GasCell &cell2) {
  double targetFlow = calculateFlow(cell1, cell2);
  if (targetFlow > 0)
    cell1.targetFlow += targetFlow;
  else
    cell2.targetFlow -= targetFlow;
}

void GasContainer2d::recalc(double dt) {
  for (size_t row = 0; row < height; ++row) {
    for (size_t column = 0; column < width; ++column) {
      auto &cell = storage[row][column];
      if (row < height - 1) increase(cell, storage[row + 1][column]);
      if (column < width - 1) increase(cell, storage[row][column + 1]);
      cell.particlesFlow = std::min(cell.targetFlow, cell.amountOfGas);
      temporary[row][column] = cell;
    }
  }
}

void GasContainer2d::moveFlow(double dt) {
  for (size_t row = 0; row < height; ++row) {
    for (size_t column = 0; column < width; ++column) {

      auto &cell = temporary[row][column];

      if (row < height - 1) {
        double targetFlow = calculateFlow(storage[row][column], storage[row + 1][column]);
        simulate(cell, temporary[row + 1][column], targetFlow);
      }

      if (column < width - 1) {
        double targetFlow = calculateFlow(storage[row][column], storage[row][column + 1]);
        simulate(cell, temporary[row][column + 1], targetFlow);
      }
      cell.targetFlow = cell.particlesFlow = 0;
    }
  }
  swap(temporary, storage);
}

void GasContainer2d::simulate(GasCell &cell1, GasCell &cell2, double targetFlow) {
  if (targetFlow > 0) {
    if (cell1.targetFlow == 0) return;

    cell2.add(cell1.slice(targetFlow * cell1.particlesFlow / cell1.targetFlow));
  } else {
    if (cell2.targetFlow == 0) return;

    cell1.add(cell2.slice(-targetFlow * cell2.particlesFlow / cell2.targetFlow));
  }
}

GasCell GasCell::slice(double particlesCount) {
  GasCell newCell(particlesCount, color, temperature);
  amountOfGas -= particlesCount;
  return newCell;
}

void GasCell::add(GasCell cell) {
  color = (color * amountOfGas + cell.color * cell.amountOfGas) / (amountOfGas + cell.amountOfGas);
  temperature = (temperature * amountOfGas + cell.temperature * cell.amountOfGas) / (amountOfGas + cell.amountOfGas);
  amountOfGas += cell.amountOfGas;
}

unreal_fluid::physics::IPhysicalObject::Type GasContainer2d::getType() {
  return Type::GAS_CONTAINER_2D;
}

void *GasContainer2d::getData() {
  return &storage;
}

void GasContainer2d::simulate(double dt) {
  recalc(dt);
  moveFlow(dt);
  diffuse();
}

void GasContainer2d::diffuse(GasCell &cell1, GasCell &cell2) {
  double slicingPart = std::min(cell1.amountOfGas, cell2.amountOfGas) / 4;
  auto cell_1 = cell1.slice(slicingPart), cell_2 = cell2.slice(slicingPart);
  cell1.add(cell_2), cell2.add(cell_1);
}

void GasContainer2d::diffuse() {
  for (size_t row = 0; row < height; ++row) {
    for (size_t column = 0; column < width; ++column) {
      auto &cell = storage[row][column];
      if (row < height - 1) diffuse(cell, storage[row + 1][column]);
      if (column < width - 1) diffuse(cell, storage[row][column + 1]);
    }
  }
}
