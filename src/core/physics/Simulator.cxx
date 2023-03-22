/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Simulator.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Simulator.h"
#include "fluid/CollisionPairs.h"

using namespace unreal_fluid::physics;

void Simulator::addPhysicalObject(IPhysicalObject *physicalObject) {
    if (physicalObject->getType() == IPhysicalObject::Type::SOLID_SPHERE) {
        solidObjects.push_back((solid::ISolid *) physicalObject);
    } else {
        dynamicObjects.push_back(physicalObject);
    }
}

void Simulator::simulate(double dt) {
    for (auto &physObject: dynamicObjects) {
        physObject->simulate(dt);
    }

    for (auto &physObject: dynamicObjects) {
        for (auto & solidObject : solidObjects) {
            interact(physObject, solidObject);
        }
    }
}

void Simulator::clearData() {
    dynamicObjects.clear();
    solidObjects.clear();
}

void Simulator::interact(IPhysicalObject *dynamicObject, solid::ISolid *solid) {
   if (dynamicObject->getType() == IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER){
       auto fluid = (fluid::SimpleFluidContainer*)dynamicObject;
       if (solid->getType() == IPhysicalObject::Type::SOLID_SPHERE){
           auto sphere = (solid::SolidSphere*)solid;
           for (auto & particle : fluid->particles) {
               if ((particle->position - sphere->position).len() <= particle->radius + sphere->radius){
                   fluid::CollisionPairs::particleAndSolidSphere(particle, sphere, fluid->k);
               }
           }
       }
   }
}

// end of Simulator.cpp
