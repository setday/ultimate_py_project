/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : SpotLight.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../BasicLight.h"

namespace unreal_fluid::render::light {
  struct SpotLight : public BasicLight {
    float cutOff = 0.0f;
    float outerCutOff = 0.0f;

    SpotLight(const vec3f &position, const vec3f &direction, const vec3f &color, float intensity, float radius) {
      this->position = position;
      this->direction = direction;
      this->color = color;
      this->intensity = intensity;
      this->radius = radius;

      type = 3;
    }
  };
} // unreal_fluid::render::light
