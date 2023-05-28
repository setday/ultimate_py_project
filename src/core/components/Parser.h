/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Parser.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../utils/math/Line2D.h"
#include "../physics/fluid/Particle.h"
#include "../physics/solid/mesh/Plane.h"
#include "../physics/solid/mesh/Triangle.h"
#include "../physics/solid/sphere/SolidSphere.h"

namespace unreal_fluid::physics {

  class Parser {
  public:
    static void sphereParse();

  };

} // namespace unreal_fluid::physics

// end of CollisionSolver.h
