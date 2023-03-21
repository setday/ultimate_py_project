/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.h
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once
#include "../IPhysicalObject.h"
#include "../../../utils/math/MathHeaders"

namespace unreal_fluid::physics::solid{
    class SolidSphere : public IPhysicalObject{
        vec3 position{};
        double radius;
    public:
        SolidSphere(vec3 position, double radius);
        ~SolidSphere() override = default;
        Type getType() override;
        void *getData() override;

    private:
        void simulate(double dt) override;

    public:
        [[nodiscard]] const vec3 &getPosition() const;
        [[nodiscard]] double getRadius() const;
    };
}


