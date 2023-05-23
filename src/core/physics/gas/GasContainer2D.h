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
    double particleCount = 1;
    int volume = 1;
    double temperature = 1;
    vec3f color = {1, 1, 1}; // color is a quantity to define gas

    GasCell() = default;
    explicit GasCell(int particleCount);

    double getPressure() const;
  };

  class GasContainer2d : public IPhysicalObject {

    int height, width;
    std::vector<std::vector<GasCell>> storage;

  public:
    GasContainer2d(int height, int width, int particle_number);
    //    void simulate(GasCell &cell1, GasCell &cell2, double dt);

    void simulate(GasCell &cell, GasCell &cell1, GasCell &cell2, GasCell &cell3, GasCell &cell4, double dt);

    void slice(GasCell &cell, double pressure);

    void add(GasCell &cell, double pressure);

    void simulationStage(double dt);

    /* abstract class implementation */

    Type getType() override;
    void *getData() override;

  private:
    void simulate(double dt) override;
  };

} // namespace unreal_fluid::physics::gas

// end of GasContainer2D.h