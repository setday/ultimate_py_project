/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.h
 * PURPOSE   : Die to born
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../physics/PhysicsObject.h"
#include "../render/components/RenderObject.h"

namespace unreal_fluid {
  class ObjectFactory;
} // namespace unreal_fluid

namespace unreal_fluid {
  class AbstractObject {
    friend ObjectFactory;

    physics::PhysicsObject *_physicsObject;
    render::RenderObject *_renderObject;

  public:
    AbstractObject() = default; /// TODO: should be protected
    AbstractObject(physics::PhysicsObject *physicsObject,
                   render::RenderObject *renderObject) : _physicsObject(physicsObject),
                                                         _renderObject(renderObject) {} // TODO: should be deleted

  public:
    ~AbstractObject();

    /// Get physics object.
    /// @return Physics object.
    physics::PhysicsObject *getPhysicsObject() const;
    /// Get render object.
    /// @return Render object.
    render::RenderObject *getRenderObject() const;
  }; // end of AbstractObject class
} // namespace unreal_fluid

// end of AbstractObject.h
