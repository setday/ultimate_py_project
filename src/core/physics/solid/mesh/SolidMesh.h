/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.cxx
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */


#pragma oncw
#include "../ISolid.h"
#include "Triangle.h"
#include "vector"

namespace unreal_fluid::physics{
    class Simulator;
}

namespace unreal_fluid::physics::solid{
    class SolidMesh : public ISolid{
        friend class Simulator;
    private:
        std::vector<Triangle> triangles;
    public:
        explicit SolidMesh(std::vector<Triangle> triangles);

        ~SolidMesh() override = default;

        Type getType() override;

        void *getData() override;

    private:
        void simulate(double dt) override;
    };
}



