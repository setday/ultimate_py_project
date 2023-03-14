/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysicsDefs.h
 * PURPOSE   : physical constants nd other definitions
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <string>

#include "../../Definitions.h"

namespace physics {
  const vec3 G = {0.0, -9.81, 0.0};
}

struct fluidDescriptor {
  std::string name;
  double particleRadius;
  double particleMass;
};