/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Flag.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "./../spring_constraint/SpringConstraint.h"

namespace unreal_fluid::addons::physics {
  class Flag {
    friend class FlagParser;

    std::vector<PhysicsBody> _points;
    std::vector<SpringConstraint> _constraints;

    int _widthSegments = 50;
    int _heightSegments = 50;

  public:
    /// @brief Creates a flag.
    /// @param width Width of the flag.
    /// @param height Height of the flag.
    /// @param widthSegments Number of segments along the width.
    /// @param heightSegments Number of segments along the height.
    Flag(double width, double height, int widthSegments = 50, int heightSegments = 50);

    /// @brief Updates the flag.
    /// @param dt Time step.
    void update(double dt);
  };
} // unreal_fluid::addons::physics

// end of Flag.h
