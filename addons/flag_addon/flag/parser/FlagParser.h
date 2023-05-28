/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : FlagParser.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "./../Flag.h"
#include "./../../../../src/core/render/components/RenderObject.h"

namespace unreal_fluid::addons::physics {
  class FlagParser {
    /// @brief Parses the flag.
    /// @param flag Flag to parse.
    /// @param renderObject Render object to parse to.
    static void parse(const Flag &flag, render::RenderObject * &renderObject);
  };
} // unreal_fluid::addons::physics

// end of FlagParser.h
