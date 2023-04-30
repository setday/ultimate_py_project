/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : DirectionalLight.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../BasicLight.h"

namespace unreal_fluid::render::light {
  struct DirectionalLight : public BasicLight {
    DirectionalLight(const vec3f &direction, const vec3f &color) {
      this->direction = direction;
      this->color = color;

      type = 1;
    }
  };
} // unreal_fluid::render::light

// end of DirectionalLight.h
