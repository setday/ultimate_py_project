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

#include "SolidSphere.h"

unreal_fluid::physics::solid::SolidSphere::SolidSphere(vec3 position, double radius) {
    this->position = position;
    this->radius = radius;
}

unreal_fluid::physics::IPhysicalObject::Type unreal_fluid::physics::solid::SolidSphere::getType() {
    return unreal_fluid::physics::IPhysicalObject::Type::SOLID_SPHERE;
}

void *unreal_fluid::physics::solid::SolidSphere::getData() {
    return this;
}

const vec3 &unreal_fluid::physics::solid::SolidSphere::getPosition() const {
    return position;
}

double unreal_fluid::physics::solid::SolidSphere::getRadius() const {
    return radius;
}

void unreal_fluid::physics::solid::SolidSphere::simulate(double dt) {}


