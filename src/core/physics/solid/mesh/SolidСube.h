/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidСube.h
 * PURPOSE   : cube implementation
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */


#pragma once

#include "../ISolid.h"

namespace unreal_fluid::physics::solid {
  class SolidCube : public ISolid {

  private:
    void simulate(double dt) override{}; // static class

  public:
    SolidCube(int size);

    /// Get type of object
    /// @return type of object
    Type getType() override;
    /// Get data stored in a physical container
    /// @return data stored in a physical container
    void *getData() override;
  };
} // namespace unreal_fluid::physics::solid

// end of SolidSphere.h

// end of SolidQube.h