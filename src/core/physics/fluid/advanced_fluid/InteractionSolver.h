/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : ultimate_py_project
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : InteractionSolver.h
* PURPOSE   : solve interactions
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#pragma once

#include "../CellsDistributor.h"
#include "../../CollisionSolver.h"
#include "thread"

namespace unreal_fluid::physics::fluid{
  class InteractionSolver {
  private:
    int coreNumber;
    std::vector<CellsDistributor> distributors;
    std::vector<std::thread> interactionTasks;
  public:
    InteractionSolver();
    ~InteractionSolver() = default;
    void interact(std::vector<Particle *> &particles, double k);
  };
}

