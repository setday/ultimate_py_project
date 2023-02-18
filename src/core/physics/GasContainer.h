/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasContainer.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "PhysicsObject.h"

namespace unreal_fluid::physics {
    class GasContainer : physics::PhysicalObject {
    public:
        GasContainer();

        ~GasContainer();

    private:
        void simulate(double) override;
    };
}