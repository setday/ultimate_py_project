/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasContainer.h
 * PURPOSE   : base gas implementation
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../Simulator.h"
#include "GasCell.h"

namespace unreal_fluid::physics::gas {
  class GasContainer : public IPhysicalObject {
    int _height;
    int _width;
    int _depth;
    std::vector<std::vector<std::vector<GasCell>>> _storage;

  public:
    GasContainer(int height, int width, int depth);

  public:
    /* abstract class implementation */

    [[nodiscard]] Type getType() override;
    [[nodiscard]] void *getData() override;

  private:
    /// @brief Simulate gas container.
    /// @param dt time step
    void simulate(double dt) override;
  };
}

// end of GasContainer.h