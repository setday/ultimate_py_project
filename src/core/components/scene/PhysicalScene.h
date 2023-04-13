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
    double dt = 0.02;

  public:
<<<<<<<< HEAD:src/core/components/ObjectFactory.h
    enum class Type {
      FluidObject,
      GasObject,
      StaticObject
    };

    static AbstractObject *create(Type type);
========
    /// Update scene.
    void update() override;
>>>>>>>> dev:src/core/components/scene/PhysicalScene.h
  };
}; // namespace unreal_fluid

// end of PhysicalScene.h
