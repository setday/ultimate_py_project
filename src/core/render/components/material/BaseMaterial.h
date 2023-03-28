/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : BaseMaterial.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::render::material {
  struct BaseMaterial {
    float shininess = 32.0f;
    float specularStrength = 0.5f;

    vec3f ambientColor = vec3f(0.1f, 0.1f, 0.1f);
    vec3f diffuseColor = vec3f(0.5f, 0.5f, 0.5f);
    vec3f specularColor = vec3f(1.0f, 1.0f, 1.0f);

    float reflectionStrength = 0.5f;
    float refractionStrength = 0.5f;
    float refractionIndex = 1.5f;
  };
} // unreal_fluid::render::material

// end of BaseMaterial.h
