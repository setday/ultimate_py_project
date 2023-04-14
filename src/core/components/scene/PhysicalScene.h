/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysicalScene.h
 * PURPOSE   : Class that realizes update of physical scene.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "IScene.h"

namespace unreal_fluid {
  class PhysicalScene : public virtual IScene {
    double dt = 0.01;

  public:
    /// Update scene.
    void update() override;
  };
}; // namespace unreal_fluid

// end of PhysicalScene.h
