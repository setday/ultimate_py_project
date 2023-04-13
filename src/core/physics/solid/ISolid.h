/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
<<<<<<<< HEAD:src/core/components/scene/IScene.h
 * FILE NAME : IScene.h
 * PURPOSE   : Interface of scene.
========
 * FILE NAME : SimpleFluidContainer.cxx
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
>>>>>>>> dev:src/core/physics/solid/ISolid.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */


#pragma once

<<<<<<<< HEAD:src/core/components/scene/IScene.h
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
========
#include "../IPhysicalObject.h"

namespace unreal_fluid::physics::solid {
  class ISolid : public IPhysicalObject {
  public:
    vec3 position{};

    ISolid() = default;
    explicit ISolid(vec3 position) : position(position) {}
  };
} // namespace unreal_fluid::physics::solid

// end of ISolid.h
>>>>>>>> dev:src/core/physics/solid/ISolid.h
