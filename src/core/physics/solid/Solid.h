/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Solid.h
 * PURPOSE   :
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../PhysicalObject.h"

namespace unreal_fluid::physics::solid {
  class Solid : PhysicalObject {
    PhysicalObject::Type getType() override;
  };
}

// end of Solid.h