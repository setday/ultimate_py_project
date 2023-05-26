/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : MaterialPresets.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "BasicMaterial.h"

namespace unreal_fluid::render::material {
  /* Metals */
  struct Gold : BasicMaterial {
    Gold() : BasicMaterial() {
      ambientColor = vec3f(0.24725f, 0.1995f, 0.0745f);
      diffuseColor = vec3f(0.75164f, 0.60648f, 0.22648f);
      specularColor = vec3f(0.628281f, 0.555802f, 0.366065f);

      specularStrength = 0.4f;

      shininess = 51.2f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Gold";
    }
  };

  struct Silver : BasicMaterial {
    Silver() : BasicMaterial() {
      ambientColor = vec3f(0.19225f, 0.19225f, 0.19225f);
      diffuseColor = vec3f(0.50754f, 0.50754f, 0.50754f);
      specularColor = vec3f(0.508273f, 0.508273f, 0.508273f);

      specularStrength = 0.4f;

      shininess = 51.2f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Silver";
    }
  };

  struct Copper : BasicMaterial {
    Copper() : BasicMaterial() {
      ambientColor = vec3f(0.19125f, 0.0735f, 0.0225f);
      diffuseColor = vec3f(0.7038f, 0.27048f, 0.0828f);
      specularColor = vec3f(0.256777f, 0.137622f, 0.086014f);

      specularStrength = 0.1f;

      shininess = 12.8f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Copper";
    }
  };

  struct Bronze : BasicMaterial {
    Bronze() : BasicMaterial() {
      ambientColor = vec3f(0.2125f, 0.1275f, 0.054f);
      diffuseColor = vec3f(0.714f, 0.4284f, 0.18144f);
      specularColor = vec3f(0.393548f, 0.271906f, 0.166721f);

      specularStrength = 0.2f;

      shininess = 25.6f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Bronze";
    }
  };

  struct Chrome : BasicMaterial {
    Chrome() : BasicMaterial() {
      ambientColor = vec3f(0.25f, 0.25f, 0.25f);
      diffuseColor = vec3f(0.4f, 0.4f, 0.4f);
      specularColor = vec3f(0.774597f, 0.774597f, 0.774597f);

      specularStrength = 0.6f;

      shininess = 76.8f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Chrome";
    }
  };

  struct Brass : BasicMaterial {
    Brass() : BasicMaterial() {
      ambientColor = vec3f(0.329412f, 0.223529f, 0.027451f);
      diffuseColor = vec3f(0.780392f, 0.568627f, 0.113725f);
      specularColor = vec3f(0.992157f, 0.941176f, 0.807843f);

      specularStrength = 0.21794872f;

      shininess = 27.897436f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Brass";
    }
  };

  /* Plastics */
  struct BlackPlastic : BasicMaterial {
    BlackPlastic() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.01f, 0.01f, 0.01f);
      specularColor = vec3f(0.50f, 0.50f, 0.50f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "BlackPlastic";
    }
  };

  struct CyanPlastic : BasicMaterial {
    CyanPlastic() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.1f, 0.06f);
      diffuseColor = vec3f(0.0f, 0.50980392f, 0.50980392f);
      specularColor = vec3f(0.50196078f, 0.50196078f, 0.50196078f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "CyanPlastic";
    }
  };

  struct GreenPlastic : BasicMaterial {
    GreenPlastic() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.1f, 0.35f, 0.1f);
      specularColor = vec3f(0.45f, 0.55f, 0.45f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "GreenPlastic";
    }
  };

  struct RedPlastic : BasicMaterial {
    RedPlastic() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.5f, 0.0f, 0.0f);
      specularColor = vec3f(0.7f, 0.6f, 0.6f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "RedPlastic";
    }
  };

  struct WhitePlastic : BasicMaterial {
    WhitePlastic() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.55f, 0.55f, 0.55f);
      specularColor = vec3f(0.70f, 0.70f, 0.70f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "WhitePlastic";
    }
  };

  struct YellowPlastic : BasicMaterial {
    YellowPlastic() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.5f, 0.5f, 0.0f);
      specularColor = vec3f(0.60f, 0.60f, 0.50f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "YellowPlastic";
    }
  };

  /* Rubbers */
  struct Rubber : BasicMaterial {
    Rubber() : BasicMaterial() {
      ambientColor = vec3f(0.02f, 0.02f, 0.02f);
      diffuseColor = vec3f(0.01f, 0.01f, 0.01f);
      specularColor = vec3f(0.4f, 0.4f, 0.4f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Rubber";
    }
  };

  struct BlackRubber : BasicMaterial {
    BlackRubber() : BasicMaterial() {
      ambientColor = vec3f(0.02f, 0.02f, 0.02f);
      diffuseColor = vec3f(0.01f, 0.01f, 0.01f);
      specularColor = vec3f(0.4f, 0.4f, 0.4f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "BlackRubber";
    }
  };

  struct CyanRubber : BasicMaterial {
    CyanRubber() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.05f, 0.05f);
      diffuseColor = vec3f(0.4f, 0.5f, 0.5f);
      specularColor = vec3f(0.04f, 0.7f, 0.7f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "CyanRubber";
    }
  };

  struct GreenRubber : BasicMaterial {
    GreenRubber() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.05f, 0.0f);
      diffuseColor = vec3f(0.4f, 0.5f, 0.4f);
      specularColor = vec3f(0.04f, 0.7f, 0.04f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "GreenRubber";
    }
  };

  struct RedRubber : BasicMaterial {
    RedRubber() : BasicMaterial() {
      ambientColor = vec3f(0.05f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.5f, 0.4f, 0.4f);
      specularColor = vec3f(0.7f, 0.04f, 0.04f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "RedRubber";
    }
  };

  struct WhiteRubber : BasicMaterial {
    WhiteRubber() : BasicMaterial() {
      ambientColor = vec3f(0.05f, 0.05f, 0.05f);
      diffuseColor = vec3f(0.5f, 0.5f, 0.5f);
      specularColor = vec3f(0.7f, 0.7f, 0.7f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "WhiteRubber";
    }
  };

  struct YellowRubber : BasicMaterial {
    YellowRubber() : BasicMaterial() {
      ambientColor = vec3f(0.05f, 0.05f, 0.0f);
      diffuseColor = vec3f(0.5f, 0.5f, 0.4f);
      specularColor = vec3f(0.7f, 0.7f, 0.04f);

      specularStrength = 0.078125f;

      shininess = 10.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "YellowRubber";
    }
  };

  /* gemstones */
  struct Emerald : BasicMaterial {
    Emerald() : BasicMaterial() {
      ambientColor = vec3f(0.0215f, 0.1745f, 0.0215f);
      diffuseColor = vec3f(0.07568f, 0.61424f, 0.07568f);
      specularColor = vec3f(0.633f, 0.727811f, 0.633f);

      specularStrength = 0.6f;

      shininess = 76.8f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Emerald";
    }
  };

  struct Jade : BasicMaterial {
    Jade() : BasicMaterial() {
      ambientColor = vec3f(0.135f, 0.2225f, 0.1575f);
      diffuseColor = vec3f(0.54f, 0.89f, 0.63f);
      specularColor = vec3f(0.316228f, 0.316228f, 0.316228f);

      specularStrength = 0.1f;

      shininess = 12.8f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Jade";
    }
  };

  struct Obsidian : BasicMaterial {
    Obsidian() : BasicMaterial() {
      ambientColor = vec3f(0.05375f, 0.05f, 0.06625f);
      diffuseColor = vec3f(0.18275f, 0.17f, 0.22525f);
      specularColor = vec3f(0.332741f, 0.328634f, 0.346435f);

      specularStrength = 0.3f;

      shininess = 38.4f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Obsidian";
    }
  };

  struct Pearl : BasicMaterial {
    Pearl() : BasicMaterial() {
      ambientColor = vec3f(0.25f, 0.20725f, 0.20725f);
      diffuseColor = vec3f(1.0f, 0.829f, 0.829f);
      specularColor = vec3f(0.296648f, 0.296648f, 0.296648f);

      specularStrength = 0.088f;

      shininess = 11.264f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Pearl";
    }
  };

  struct Ruby : BasicMaterial {
    Ruby() : BasicMaterial() {
      ambientColor = vec3f(0.1745f, 0.01175f, 0.01175f);
      diffuseColor = vec3f(0.61424f, 0.04136f, 0.04136f);
      specularColor = vec3f(0.727811f, 0.626959f, 0.626959f);

      specularStrength = 0.6f;

      shininess = 76.8f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Ruby";
    }
  };

  struct Turquoise : BasicMaterial {
    Turquoise() : BasicMaterial() {
      ambientColor = vec3f(0.1f, 0.18725f, 0.1745f);
      diffuseColor = vec3f(0.396f, 0.74151f, 0.69102f);
      specularColor = vec3f(0.297254f, 0.30829f, 0.306678f);

      specularStrength = 0.1f;

      shininess = 12.8f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Turquoise";
    }
  };

  /* glass */
  struct Glass : BasicMaterial {
    Glass() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.55f, 0.55f, 0.55f);
      specularColor = vec3f(0.7f, 0.7f, 0.7f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.3f;
      refractionStrength = 0.6f;
      refractionIndex = 1.5f;

      opacity = 0.6f;
      isTransparent = true;

      name = "Glass";
    }
  };

  /* liquid */
  struct Water : BasicMaterial {
    Water() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.55f);
      diffuseColor = vec3f(0.0f, 0.0f, 0.55f);
      specularColor = vec3f(0.5f, 0.5f, 0.5f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.1f;
      refractionStrength = 0.7f;
      refractionIndex = 1.33f;

      opacity = 0.7f;
      isTransparent = true;

      name = "Water";
    }
  };

  struct Lambertian : BasicMaterial {
    Lambertian() : BasicMaterial() {
      ambientColor = vec3f(0.0f, 0.0f, 0.0f);
      diffuseColor = vec3f(0.55f, 0.55f, 0.55f);
      specularColor = vec3f(0.7f, 0.7f, 0.7f);

      specularStrength = 0.25f;

      shininess = 32.0f;

      reflectionStrength = 0.0f;
      refractionStrength = 0.0f;
      refractionIndex = 1.0f;

      opacity = 0.0f;
      isTransparent = false;

      name = "Lamberian";
    }
  };
} // unreal_fluid::render::material

// end of MaterialPresets.h
