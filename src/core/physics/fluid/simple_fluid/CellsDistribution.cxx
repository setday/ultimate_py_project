/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CellsDistribution.cxx
 * PURPOSE   : distribute particles
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "CellsDistribution.h"

using namespace unreal_fluid::physics::fluid;

std::pair<Particle *, Particle *> CellsDistribution::nextPair() {

  if (second >= cell_iterator->second.size()) {
    first++;
    second = first + 1;
  }

  while (cell_iterator != cells.end() && second >= cell_iterator->second.size()) {
    first = 0;
    second = 1;
    cell_iterator++;
  }

  if (cell_iterator == cells.end()) return terminator;

  return {cell_iterator->second[first], cell_iterator->second[second++]};
}

CellsDistribution::CellsDistribution(std::vector<Particle *> &particles) {

  double averageRadius = 0;
  for (const auto &particle: particles) {
    averageRadius += particle->radius;
  }
  averageRadius /= particles.size();

  double dx = 1 ; // 3 * averageRadius;

  for (const auto& particle: particles) {
    auto [x, y, z] = particle->position;

    x /= dx;
    y /= dx;
    z /= dx;

    uint64_t id = ((uint64_t) x << 32) + ((uint64_t) y << 16) + (uint64_t) z;
    cells[id].push_back(particle);
  }

  first = 0;
  second = 1;

  cell_iterator = cells.begin();
  Logger::logWarning(cells.size(), particles.size(), dx, averageRadius);
}

// end of CellsDistribution.cxx
