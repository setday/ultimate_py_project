/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : IPhysicalObject.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>


namespace unreal_fluid::physics {
    class Simulator;

    class IPhysicalObject {
        friend class Simulator;

    public:
        enum class Type {
            SIMPLE_FLUID_CONTAINER,
            SOLID_SPHERE,
            SOLID_MESH
        };

        virtual ~IPhysicalObject() = default;

        virtual Type getType() = 0;

        virtual void *getData() = 0;

    private:
        virtual void simulate(double dt) = 0;
    };
} // namespace unreal_fluid::physics

// end of IPhysicalObject.h
