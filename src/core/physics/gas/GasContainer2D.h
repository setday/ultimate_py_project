/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasContainer2D.h
 * PURPOSE   : test 2-dimensional gas class
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../Simulator.h"

namespace unreal_fluid::physics::gas {

  class GasCell {
  public:
    int pressure;
    double color = 1; // color is a quantity to define gas
    GasCell() = default;

    GasCell(int pressure, int color);
  };

  class GasContainer2d {

    int height, width;
    std::vector<std::vector<GasCell>> storage;

  public:
    GasContainer2d(int height, int width, int particle_number);

    void simulate(GasCell cell1, GasCell cell2);

    void slice(GasCell cell, int pressure);

    void add(GasCell cell, int pressure);

    void simulationStage();

    void parse();

  };

} // namespace unreal_fluid::physics::gas

// end of GasContainer2D.h