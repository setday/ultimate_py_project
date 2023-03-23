/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.h
 * PURPOSE   : Abstract object to store render and physical objects in one
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../Compositor.h"
#include "../physics/PhysicalObject.h"
#include "../physics/fluid/simple_fluid/SimpleFluidContainer.h"
#include "../render/components/RenderObject.h"

namespace unreal_fluid {
  class AbstractObject {
    const compositor::Compositor *compositor;
    physics::PhysicalObject *physicalObject;
    std::vector<render::RenderObject *> renderObjects;

  public:
//    AbstractObject(physics::PhysicalObject *physObject, const compositor::Compositor *compositor);
    AbstractObject(physics::fluid::FluidDescriptor descriptor, const compositor::Compositor *compositor);
    ~AbstractObject() = default;
    [[nodiscard]] std::vector<render::RenderObject *> &getRenderObjects();
    [[nodiscard]] physics::PhysicalObject *getPhysicalObject();
    void parse();
  }; // end of AbstractObject class
} // namespace unreal_fluid
