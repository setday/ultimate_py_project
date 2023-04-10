/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Simulator.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>
#include "../../utils/math/MathHeaders"
#include "solid/sphere/SolidSphere.h"
#include "fluid/simple_fluid/SimpleFluidContainer.h"


namespace unreal_fluid::physics {
    class Simulator {
    private:
        std::vector<IPhysicalObject *> dynamicObjects;
        std::vector<IPhysicalObject *> solidObjects;
    public:
        Simulator() = default;

        ~Simulator() = default;

        /// @brief Adds IPhysicalObject to scene
        /// @details Adds IPhysicalObject into an internal buffer.
        /// Call simulate() to simulate all of the PhysObjects in the buffer
        void addPhysicalObject(IPhysicalObject *physicalObject);

        /// @brief Simulates the scene
        /// @details calls simulate() function of each IPhysicalObject in the internal buffer and solve interactions between them.
        void simulate(double dt);

    private:
        void interact(IPhysicalObject* dynamicObject, IPhysicalObject* solid);
    };
} // namespace unreal_fluid::physics

// end of Simulator.h
