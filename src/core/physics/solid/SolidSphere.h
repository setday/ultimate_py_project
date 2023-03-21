/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidSphere.h
 * PURPOSE   : Solid class
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once
#include "../../../utils/math/MathHeaders"
#include "../IPhysicalObject.h"

namespace unreal_fluid::physics::solid {
  class SolidSphere : public IPhysicalObject {
    vec3 position;
    double radius;

  private:
    void simulate(double dt) override{};

  public:
    SolidSphere(vec3 position, double radius);
    Type getType() override;
    void *getData() override;
    [[nodiscard]] const vec3 &getPosition() const;
    [[nodiscard]] double getRadius() const;
  };
} // namespace unreal_fluid::physics::solid
