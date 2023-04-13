/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.cxx
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */


#pragma once

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
