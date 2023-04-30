/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : BasicLight.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::render::light {
  struct BasicLight {
    vec3f position{0.0f, 0.0f, 0.0f};
    vec3f direction{0.0f, -1.0f, 0.0f};
    vec3f color{1.0f, 1.0f, 1.0f};

    float intensity = 1.0f;
    float radius = 1.0f;

    int type = 0; // 0 - general, 1 - directional, 2 - point, 3 - spot
  };
} // unreal_fluid::render::light

// end of BasicLight.h
