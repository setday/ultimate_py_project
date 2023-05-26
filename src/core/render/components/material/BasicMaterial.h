/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : BasicMaterial.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <string>

#include "../../../../Definitions.h"

namespace unreal_fluid::render::material {
  struct BasicMaterial {
    vec3f ambientColor = vec3f(0.1f, 0.1f, 0.1f);
    vec3f diffuseColor = vec3f(0.5f, 0.5f, 0.5f);
    vec3f specularColor = vec3f(1.0f, 1.0f, 1.0f);

    float specularStrength = 0.5f;

    float shininess = 32.0f;

    float reflectionStrength = 0.5f;
    float refractionStrength = 0.5f;
    float refractionIndex = 1.5f;

    float opacity = 1.0f;
    bool isTransparent = false;

    std::string name = "BasicMaterial";
  };
} // unreal_fluid::render::material

// end of BasicMaterial.h
