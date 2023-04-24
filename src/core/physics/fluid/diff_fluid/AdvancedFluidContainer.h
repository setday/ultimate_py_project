/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AdvancedFluidContainer.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once
#include "../IFluidContainer.h"

namespace unreal_fluid::physics::fluid {
  class AdvancedFluidContainer : public IFluidContainer {
    void advect(double dt);
    void addExternalForces(double dt);
    void interact();
  };
} // namespace unreal_fluid::physics::fluid

// end of AdvancedFluidContainer.h