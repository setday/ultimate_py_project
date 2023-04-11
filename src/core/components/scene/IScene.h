/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : IScene.h
 * PURPOSE   : Interface of scene.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>

#include "../../../Definitions.h"

#include "../../SceneCompositor.h"
#include "../AbstractObject.h"

namespace unreal_fluid {
  class IScene {
  protected:
    const compositor::SceneCompositor *compositor;

    std::vector<AbstractObject *> objects;

  public:
    IScene() = default;
    virtual ~IScene() = default;

    /// Update scene.
    virtual void update() = 0;
    /// Render scene.
    virtual void render() = 0;
  };
}

// end of IScene.h
