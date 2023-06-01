/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Triangle.h
 * PURPOSE   : triangle class used in mesh
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */
#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::physics::solid {
    struct Triangle {
    private:
        void rotateY();
        void rotateZ();
        void calculateAngles();
    private:
        vec3f v1, v2, v3;
        vec3f norm;
        vec3f rotatedV1, rotatedV2, rotatedV3;
        vec3f rotatedNorm;
        math::Angle phiY, phiZ;
    public:
        ~Triangle() = default;
        Triangle(vec3f v1, vec3f v2, vec3f v3);

        [[nodiscard]] const vec3f &getV1() const;
        [[nodiscard]] const vec3f &getV2() const;
        [[nodiscard]] const vec3f &getV3() const;
        [[nodiscard]] const vec3f &getNorm() const;
        [[nodiscard]] const vec3f &getRotatedV1() const;
        [[nodiscard]] const vec3f &getRotatedV2() const;
        [[nodiscard]] const vec3f &getRotatedV3() const;
        [[nodiscard]] const vec3f &getRotatedNorm() const;
        [[nodiscard]] const math::Angle &getPhiY() const;
        [[nodiscard]] const math::Angle &getPhiZ() const;
    };
} // namespace unreal_fluid::physics::solid

// end of Triangle.h
