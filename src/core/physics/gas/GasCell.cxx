/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : GasCell.cxx
 * FILE AUTHORS            : Daniil Martsenyuk, Serkov Alexander (co-author).
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "GasCell.h"

using namespace unreal_fluid::physics::gas;

GasCell::GasCell(double amountOfGas, vec3f color, double temperature) : amountOfGas(amountOfGas),
                                                                        color(color),
                                                                        temperature(temperature) {}

double GasCell::getPressure() const {
  const double gasConstant = 0.003; // real = 8.3144598
  return amountOfGas * gasConstant * temperature / volume;
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

// end of GasCell.cxx
