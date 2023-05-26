/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : RenderScene.h
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
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
