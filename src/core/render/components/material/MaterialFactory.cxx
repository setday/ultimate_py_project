/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : MaterialFactory.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "MaterialFactory.h"

using namespace unreal_fluid::render::material;

BaseMaterial MaterialFactory::createMaterial(MaterialType type) {
  BaseMaterial material;

  switch (type) {
    case MaterialType::GLASS:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.05f, 0.05f);
      material.diffuse_color = vec3f(0.4f, 0.5f, 0.5f);
      material.specular_color = vec3f(0.04f, 0.7f, 0.7f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::WATTER:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.05f, 0.05f);
      material.diffuse_color = vec3f(0.4f, 0.5f, 0.5f);
      material.specular_color = vec3f(0.04f, 0.7f, 0.7f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.33f;
      break;
    case MaterialType::GOLD:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.24725f, 0.1995f, 0.0745f);
      material.diffuse_color = vec3f(0.75164f, 0.60648f, 0.22648f);
      material.specular_color = vec3f(0.628281f, 0.555802f, 0.366065f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::SILVER:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.19225f, 0.19225f, 0.19225f);
      material.diffuse_color = vec3f(0.50754f, 0.50754f, 0.50754f);
      material.specular_color = vec3f(0.508273f, 0.508273f, 0.508273f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::BRONZE:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.2125f, 0.1275f, 0.054f);
      material.diffuse_color = vec3f(0.714f, 0.4284f, 0.18144f);
      material.specular_color = vec3f(0.393548f, 0.271906f, 0.166721f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::RUBY:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.1745f, 0.01175f, 0.01175f);
      material.diffuse_color = vec3f(0.61424f, 0.04136f, 0.04136f);
      material.specular_color = vec3f(0.727811f, 0.626959f, 0.626959f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::EMERALD:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0215f, 0.1745f, 0.0215f);
      material.diffuse_color = vec3f(0.07568f, 0.61424f, 0.07568f);
      material.specular_color = vec3f(0.633f, 0.727811f, 0.633f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::JADE:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.135f, 0.2225f, 0.1575f);
      material.diffuse_color = vec3f(0.54f, 0.89f, 0.63f);
      material.specular_color = vec3f(0.316228f, 0.316228f, 0.316228f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::OBSIDIAN:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.05375f, 0.05f, 0.06625f);
      material.diffuse_color = vec3f(0.18275f, 0.17f, 0.22525f);
      material.specular_color = vec3f(0.332741f, 0.328634f, 0.346435f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::PEARL:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.25f, 0.20725f, 0.20725f);
      material.diffuse_color = vec3f(1.0f, 0.829f, 0.829f);
      material.specular_color = vec3f(0.296648f, 0.296648f, 0.296648f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::TURQUOISE:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.1f, 0.18725f, 0.1745f);
      material.diffuse_color = vec3f(0.396f, 0.74151f, 0.69102f);
      material.specular_color = vec3f(0.297254f, 0.30829f, 0.306678f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::BRASS:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.329412f, 0.223529f, 0.027451f);
      material.diffuse_color = vec3f(0.780392f, 0.568627f, 0.113725f);
      material.specular_color = vec3f(0.992157f, 0.941176f, 0.807843f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::CHROME:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.25f, 0.25f, 0.25f);
      material.diffuse_color = vec3f(0.4f, 0.4f, 0.4f);
      material.specular_color = vec3f(0.774597f, 0.774597f, 0.774597f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::COPPER:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.19125f, 0.0735f, 0.0225f);
      material.diffuse_color = vec3f(0.7038f, 0.27048f, 0.0828f);
      material.specular_color = vec3f(0.256777f, 0.137622f, 0.086014f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::BLACK_PLASTIC:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.01f, 0.01f, 0.01f);
      material.specular_color = vec3f(0.50f, 0.50f, 0.50f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::CYAN_PLASTIC:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.1f, 0.06f);
      material.diffuse_color = vec3f(0.0f, 0.50980392f, 0.50980392f);
      material.specular_color = vec3f(0.50196078f, 0.50196078f, 0.50196078f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::GREEN_PLASTIC:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.1f, 0.35f, 0.1f);
      material.specular_color = vec3f(0.45f, 0.55f, 0.45f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::RED_PLASTIC:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.5f, 0.0f, 0.0f);
      material.specular_color = vec3f(0.7f, 0.6f, 0.6f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::WHITE_PLASTIC:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.55f, 0.55f, 0.55f);
      material.specular_color = vec3f(0.70f, 0.70f, 0.70f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::YELLOW_PLASTIC:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.5f, 0.5f, 0.0f);
      material.specular_color = vec3f(0.60f, 0.60f, 0.50f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::BLACK_RUBBER:
      material.shininess = 10.0f;
      material.ambient_color = vec3f(0.02f, 0.02f, 0.02f);
      material.diffuse_color = vec3f(0.01f, 0.01f, 0.01f);
      material.specular_color = vec3f(0.4f, 0.4f, 0.4f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::CYAN_RUBBER:
      material.shininess = 10.0f;
      material.ambient_color = vec3f(0.0f, 0.05f, 0.05f);
      material.diffuse_color = vec3f(0.4f, 0.5f, 0.5f);
      material.specular_color = vec3f(0.04f, 0.7f, 0.7f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::GREEN_RUBBER:
      material.shininess = 10.0f;
      material.ambient_color = vec3f(0.0f, 0.05f, 0.0f);
      material.diffuse_color = vec3f(0.4f, 0.5f, 0.4f);
      material.specular_color = vec3f(0.04f, 0.7f, 0.04f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::RED_RUBBER:
      material.shininess = 10.0f;
      material.ambient_color = vec3f(0.05f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.5f, 0.4f, 0.4f);
      material.specular_color = vec3f(0.7f, 0.04f, 0.04f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::WHITE_RUBBER:
      material.shininess = 10.0f;
      material.ambient_color = vec3f(0.05f, 0.05f, 0.05f);
      material.diffuse_color = vec3f(0.5f, 0.5f, 0.5f);
      material.specular_color = vec3f(0.7f, 0.7f, 0.7f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::YELLOW_RUBBER:
      material.shininess = 10.0f;
      material.ambient_color = vec3f(0.05f, 0.05f, 0.0f);
      material.diffuse_color = vec3f(0.5f, 0.5f, 0.4f);
      material.specular_color = vec3f(0.7f, 0.7f, 0.04f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
    case MaterialType::CUSTOM:
      material.shininess = 32.0f;
      material.ambient_color = vec3f(0.0f, 0.0f, 0.0f);
      material.diffuse_color = vec3f(0.55f, 0.55f, 0.55f);
      material.specular_color = vec3f(0.70f, 0.70f, 0.70f);
      material.specular_strength = 0.5f;
      material.reflection_strength = 0.5f;
      material.refraction_strength = 0.5f;
      material.refraction_index = 1.5f;
      break;
  }

  return material;
}
