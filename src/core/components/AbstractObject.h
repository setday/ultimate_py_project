/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.h
 * PURPOSE   : Abstract object to store render object and a physical one
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../physics/PhysObject.h"
#include "../render/components/RenderObject.h"

namespace unreal_fluid {
  class AbstractObject {

    physics::PhysObject *physObject;
    std::vector<render::RenderObject *> renderObjects;

  public:
    AbstractObject();
    ~AbstractObject();
    void render();
    void update(double dt);
    void parse();

  }; // end of AbstractObject class
} // namespace unreal_fluid
