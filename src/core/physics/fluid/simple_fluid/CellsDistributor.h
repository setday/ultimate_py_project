/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CellsDistributor.h
 * PURPOSE   : distribute particles
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <unordered_map>
#include <vector>

#include "../Particle.h"

namespace unreal_fluid::physics::fluid {
  class CellsDistributor {
  public:
    constexpr static std::pair<Particle *, Particle *> terminator = {nullptr, nullptr};
    std::vector<Particle *> big_particles;

  private:
    int first = 0;
    int second = 1;
    std::unordered_map<uint64_t, std::vector<Particle *>> cells;
    std::unordered_map<uint64_t, std::vector<Particle *>>::iterator cell_iterator;

    static uint64_t getId(vec3 position);

  public:
    CellsDistributor() = default;
    ~CellsDistributor() = default;

    /// @brief updates itself after simulation stage
    /// @details calculates new cells for each particle after simulation in fluid container
    void update(std::vector<Particle *> &particles);

    /// @brief returns next pair
    /// @details Returns next pair of particles in cell. If cell is used, goes to the next cell.
    std::pair<Particle *, Particle *> nextPair();
  };
} // namespace unreal_fluid::physics::fluid
