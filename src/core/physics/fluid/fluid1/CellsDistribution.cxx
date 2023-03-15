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
  while (cell.size() < 2 && current_cell < cells.size()) {
    cell = cells[cells_keys[++current_cell]];
  }
  if (current_cell == cells.size()) return {nullptr, nullptr};
  if (second >= cell.size()) ++first, second = first + 1;
  while (first >= cell.size() - 1 && current_cell < cells.size()) {
    cell = cells[cells_keys[++current_cell]];
    first = 0, second = 1;
  }
  if (current_cell == cells.size()) return {nullptr, nullptr};
  return {cell[first], cell[second++]};
}

CellsDistribution::CellsDistribution(std::vector<Particle> &particles) {
  counter = 0, taken = 0;
  uint64_t id;
  int dx = 1, dy = 1, dz = 1; /// TODO: what should these constants be?
  for (auto &particle: particles) {
    ++counter;
    auto [x, y, z] = particle.coords;
    x /= dx;
    y /= dy;
    z /= dz;
    id = ((uint64_t) x << 32) + ((uint64_t) y << 16) + (uint64_t) z;
    cells[id].push_back(&particle);
  }
  int k = 0;
  for (auto [key, value]: cells) {
    cells_keys[k] = key;
    ++k;
  }
  assert(k > 0);
  cell = cells[cells_keys[0]];
  current_cell = 0;
  first = 0, second = 1;
}
