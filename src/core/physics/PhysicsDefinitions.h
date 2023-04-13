/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
<<<<<<<< HEAD:src/core/components/scene/RenderScene.h
 * FILE NAME : RenderScene.h
 * PURPOSE   : Class that realizes render of scene.
========
 * FILE NAME : PhysicsDefinitions.h
 * PURPOSE   : physical constants
>>>>>>>> dev:src/core/physics/PhysicsDefinitions.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

<<<<<<<< HEAD:src/core/components/scene/RenderScene.h
#include "IScene.h"

namespace unreal_fluid {
  class RenderScene : public virtual IScene {
  public:
    /// Render scene.
    void render() override;
  };
};

// end of RenderScene.h
========
#include "../../Definitions.h"

namespace unreal_fluid::physics {
  const vec3 G = {0.0, -9.81, 0.0};
}

// end of PhysicsDefinitions.h
>>>>>>>> dev:src/core/physics/PhysicsDefinitions.h
