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

#include "../SceneCompositor.h"
#include "../render/components/RenderObject.h"
#include "../physics/fluid/simple_fluid/SimpleFluidContainer.h"
#include "../physics/solid/sphere/SolidSphere.h"

namespace unreal_fluid {
  class AbstractObject {
    physics::IPhysicalObject *physicalObject;
    std::vector<render::RenderObject *> renderObjects;

  public:
    AbstractObject(physics::IPhysicalObject *physicalObject, const std::vector<render::RenderObject *> &renderObjects);
    explicit AbstractObject(physics::IPhysicalObject *physObject);
    explicit AbstractObject(physics::fluid::FluidDescriptor descriptor);

    /// Get render object.
    /// @return Render object.
    [[nodiscard]] std::vector<render::RenderObject *> &getRenderObjects();
    /// Get physics object.
    /// @return Physics object.
    [[nodiscard]] physics::IPhysicalObject *getPhysicalObject();

    void parse();
  }; // end of AbstractObject class
} // namespace unreal_fluid

// end of AbstractObject.h
