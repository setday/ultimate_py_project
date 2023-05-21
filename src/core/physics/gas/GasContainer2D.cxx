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

GasCell::GasCell(double amountOfGas, vec3f color) : amountOfGas(amountOfGas),
                                                    color(color) {}

double GasCell::getPressure() const {
  const double gasConstant = 0.003;// real = 8.3144598

  return amountOfGas * gasConstant * temperature / volume;
}

GasContainer2d::GasContainer2d(int height, int width, int particle_number) : height(height),
                                                                             width(width),
                                                                             storage(height) {
  for (auto &row: storage) row.resize(width);

  for (int counter = 0; counter < particle_number; ++counter) {
    int x = rand() % (height / 3 + 1), y = rand() % (width / 3 + 1);
    storage[x][y] = GasCell(rand() % 20 + 2,vec3(rand() % 2, rand() % 2, rand() % 2));
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
  double pressureDiff = (cell.getPressure() - meanPressure) / 3;
  if (pressureDiff > 0) { // давление в клетке больше, чем в соседях
    cell1.add(cell.slice(pressureDiff));
    cell2.add(cell.slice(pressureDiff));
    cell3.add(cell.slice(pressureDiff));
    cell4.add(cell.slice(pressureDiff));
  } else {
    cell.add(cell1.slice(-pressureDiff));
    cell.add(cell2.slice(-pressureDiff));
    cell.add(cell3.slice(-pressureDiff));
    cell.add(cell4.slice(-pressureDiff));
  }
}

GasCell GasCell::slice(double amountOfGas) {
  double realSlice = std::min(amountOfGas, this->amountOfGas);
  GasCell newCell(realSlice, color);
  newCell.temperature = temperature;
  this->amountOfGas -= realSlice;
  return newCell;
}

void GasCell::add(GasCell cell) {
  this->color = (this->color * this->amountOfGas + cell.color * cell.amountOfGas) / (this->amountOfGas + cell.amountOfGas);
  this->temperature = (this->temperature * this->amountOfGas + cell.temperature * cell.amountOfGas) / (this->amountOfGas + cell.amountOfGas);
  this->amountOfGas += cell.amountOfGas;
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
