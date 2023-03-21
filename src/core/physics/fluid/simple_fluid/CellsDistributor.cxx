/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CellsDistributor.cxx
 * PURPOSE   : distribute particles
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "CellsDistributor.h"

using namespace unreal_fluid::physics::fluid;

std::pair<Particle *, Particle *> CellsDistributor::nextPair() {

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

CellsDistributor::CellsDistributor(std::vector<Particle *> &particles) {

  double averageRadius = 0;
  for (const auto &particle: particles) averageRadius += particle->radius;
  averageRadius /= particles.size();

  double cellSize = 5 * averageRadius;

  for (const auto &particle: particles) {
    if (particle->radius >= cellSize) {
      big_particles.push_back(particle);
      continue;
    }

    math::Vector3<uint64_t> position = particle->position / cellSize;
    for (const auto &diff: bias) {
      if (((position + diff) * cellSize).len() <= particle->radius && (position + diff).x >= 0 && (position + diff).y >= 0 && (position + diff).z >= 0) {
        cells[getId(position + diff)].push_back(particle);
      }
    }
  }

  first = 0;
  second = 1;
  cell_iterator = cells.begin();
}

std::vector<Particle *> &CellsDistributor::getBigParticles() {
  return big_particles;
}

uint64_t CellsDistributor::getId(vec3 position) {
  return ((uint64_t) (position.x) << 32) + ((uint64_t) (position.y) << 16) + (uint64_t) position.z;
}

// end of CellsDistributor.cxx
