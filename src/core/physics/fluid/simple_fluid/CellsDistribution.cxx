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

  if (cell_iterator == cells.end()) return terminator;

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
  /// TODO correct Cell Distribution of the particles. If the radius is large than dx, the distribution is not correct!

  double averageRadius = 0;
  for (int i = 0; i < particles.size(); ++i) {
    averageRadius += particles[i]->radius / particles.size();
  }

  auto dx = 1; /// TODO dx should be equal to const*averageRadius; (const in [4..10]);

  for (Particle *particle: particles) {
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
