/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CellsDistribution.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <unordered_map>
#include <vector>
#include "../Particle.h"

namespace unreal_fluid::physics::fluid {
  class CellsDistribution {
    friend class SimpleFluidContainer;

    CellsDistribution(std::vector<Particle> &particles);
    ~CellsDistribution() = default;

    uint64_t taken, counter, current_cell, first, second;
    const int N = 1000; // world of cells size
    std::unordered_map<uint64_t, std::vector<Particle *>> cells;
    std::unordered_map<uint64_t, uint64_t> cells_keys;
    std::vector<Particle *> cell;

    std::pair<Particle *, Particle *> nextPair();
  };
} // namespace unreal_fluid::physics::fluid

// end of CellsDistribution.h