/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : PointLight.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../BasicLight.h"

namespace unreal_fluid::render::light {
  struct PointLight : public BasicLight {
    PointLight(const vec3f &position, const vec3f &color, float intensity) {
      this->position = position;
      this->color = color;
      this->intensity = intensity;

      type = 2;
    }
  };
} // unreal_fluid::render::light
