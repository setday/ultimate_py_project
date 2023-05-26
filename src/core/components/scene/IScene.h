/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : IScene.h
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Interface of scene.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <vector>

#include "../../../Definitions.h"

#include "../../SceneCompositor.h"
#include "../AbstractObject.h"

namespace unreal_fluid {
  class IScene {
  protected:
    const compositor::SceneCompositor *compositor = nullptr;
    std::vector<AbstractObject *> objects;

  public:
    IScene() = default;
    virtual ~IScene() = default;

    /// Update scene.
    virtual void update() = 0;
    /// Render scene.
    virtual void render() = 0;
  };
} // namespace unreal_fluid

// end of IScene.h
