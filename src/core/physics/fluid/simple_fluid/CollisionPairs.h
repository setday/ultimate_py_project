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
#include "../Particle.h"
#include "../../solid/SolidSphere.h"

namespace unreal_fluid::physics::fluid{
    class CollisionPairs{
    public:
        static void particleAndParticle(Particle* p1, Particle* p2, double k);
        static void particleAndSolidSphere(Particle* p, solid::SolidSphere* solid, double k);
    };

}
