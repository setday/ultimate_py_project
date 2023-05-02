/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClInteractionSolver.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "ClInteractionSolver.h"

using namespace unreal_fluid::physics::fluid::helper;

ClInteractionSolver::ClInteractionSolver(std::vector<Particle*>& particles) {
    this->particles = particles;
    ///TODO init CL resources
}

void ClInteractionSolver::interact() {
    ///TODO interact on GPU
}

ClInteractionSolver::~ClInteractionSolver() {
    ///TODO free CL resources
}
