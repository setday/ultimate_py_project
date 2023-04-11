/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : RenderScene.h
 * PURPOSE   : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "IScene.h"

namespace unreal_fluid {
  class RenderScene : public virtual IScene {
  public:
    /// Render scene.
    void render() override;
  };
};

// end of RenderScene.h
