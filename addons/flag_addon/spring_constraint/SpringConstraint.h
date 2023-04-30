/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : SpringConstraint.h
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "./../physics_body/PhysicsBody.h"

namespace unreal_fluid::addons::physics {
  struct SpringConstraint {
    PhysicsBody *body1;
    PhysicsBody *body2;

    float stiffness;
    float damping;

    float restLength;

    SpringConstraint(PhysicsBody *body1, PhysicsBody *body2, float stiffness, float damping, float restLength)
        : body1(body1), body2(body2), stiffness(stiffness), damping(damping), restLength(restLength) {}

    /// @brief Updates the constraint.
    void update();
  };
} // unreal_fluid::addons::physics

// end of SpringConstraint.h
