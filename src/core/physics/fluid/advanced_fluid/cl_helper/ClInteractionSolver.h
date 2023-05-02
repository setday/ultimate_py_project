/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClInteractionSolver.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../AdvancedFluidContainer.h"

namespace unreal_fluid::physics::fluid::helper {
        class ClInteractionSolver {
        private:
            std::vector<Particle *> particles;
        public:
            explicit ClInteractionSolver(std::vector<Particle *> &particles);

            void interact();

            ~ClInteractionSolver();
        };
    }



