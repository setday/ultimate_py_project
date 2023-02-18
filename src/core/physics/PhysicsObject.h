/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysicsObject.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../Core.h"
#include "vector"

namespace unreal_fluid::physics {
    class PhysicalObject {
    private:
        //std::vector<StaticObject> solids;
    public:
        PhysicalObject() = default;

        ~PhysicalObject() = default;

        virtual void simulate(double) = 0;
    };
}


// end of PhysicsObject.h