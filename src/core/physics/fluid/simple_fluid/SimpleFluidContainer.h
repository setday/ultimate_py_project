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

#include "../../PhysicsDefinitions.h"
#include "../IFluidContainer.h"
#include "CellsDistributor.h"
#include "../../Simulator.h"

namespace unreal_fluid::physics {
    class Simulator;
}

namespace unreal_fluid::physics::fluid {
    class SimpleFluidContainer : public IFluidContainer {
        friend class ::unreal_fluid::physics::Simulator;

    private:
        double k;

    public:
        explicit SimpleFluidContainer(FluidDescriptor descriptor);

        ~SimpleFluidContainer() override;

        IPhysicalObject::Type getType() override;

        void *getData() override;

    private:

        void simulate(double dt) override;

        void collide(Particle *p1, Particle *p2) const;

        void advect(double dt);

        void addExternalForces(double dt);

        void interact();

        void addParticle(vec3 position, vec3 velocity, double radius, double mass);
    };
} // namespace unreal_fluid::physics::fluid

// end of FluidContainer.h
