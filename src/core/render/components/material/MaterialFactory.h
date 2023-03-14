/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : MaterialFactory.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "BaseMaterial.h"

namespace unreal_fluid::render::material {
  class MaterialFactory {
  public:
    enum class MaterialType {
      GLASS,
      WATTER,
      GOLD,
      SILVER,
      BRONZE,
      RUBY,
      EMERALD,
      JADE,
      OBSIDIAN,
      PEARL,
      TURQUOISE,
      BRASS,
      CHROME,
      COPPER,
      BLACK_PLASTIC,
      CYAN_PLASTIC,
      GREEN_PLASTIC,
      RED_PLASTIC,
      WHITE_PLASTIC,
      YELLOW_PLASTIC,
      BLACK_RUBBER,
      CYAN_RUBBER,
      GREEN_RUBBER,
      RED_RUBBER,
      WHITE_RUBBER,
      YELLOW_RUBBER,
      CUSTOM
    };

    static BaseMaterial createMaterial(MaterialType type);
  };
}

// end of MaterialFactory.h
