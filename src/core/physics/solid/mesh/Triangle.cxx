/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Triangle.cxx
 * PURPOSE   : triangle class used in mesh
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Triangle.h"

using namespace unreal_fluid::physics::solid;

Triangle::Triangle(vec3f v1, vec3f v2, vec3f v3) {
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    norm = ((v2 - v1).cross(v3 - v1)).normalize();
    rotatedV1 = v1;
    rotatedV2 = v2;
    rotatedV3 = v3;
    rotatedNorm = norm;
    calculateAngles();
    rotateZ();
}

void Triangle::calculateAngles() {
    if (rotatedNorm.x == 0 && rotatedNorm.z == 0){
        phiY.cos = 1;
        phiY.sin = 0;
        phiZ.cos = 1;
        phiZ.sin = 0;
        rotateY();
        return;
    }
    phiY.cos = rotatedNorm.x / sqrt(rotatedNorm.x * rotatedNorm.x + rotatedNorm.z * rotatedNorm.z);
    phiY.sin = std::sqrt(1 - phiY.cos*phiY.cos);
    if (rotatedNorm.z < 0){
        phiY.sin *= -1;
    }
    rotateY();
    double cosZ, sinZ;
    if (rotatedNorm.x == 0 && rotatedNorm.y == 0){
        cosZ = 1;
        sinZ = 0;
        phiZ.cos = cosZ;
        phiZ.sin = sinZ;
    }else
        cosZ = rotatedNorm.y / std::sqrt(rotatedNorm.x * rotatedNorm.x + rotatedNorm.y * rotatedNorm.y);
    sinZ = sqrt(1 - cosZ*cosZ);
    if (rotatedNorm.y < 0) {
        sinZ *= -1;
    }
    phiZ.cos = cosZ;
    phiZ.sin = sinZ;
}

void Triangle::rotateZ() {
    rotatedV1.rotateZSelf(phiZ);
    rotatedV2.rotateZSelf(phiZ);
    rotatedV3.rotateZSelf(phiZ);
    rotatedNorm.rotateZSelf(phiZ);
}

void Triangle::rotateY() {
    rotatedV1.rotateYSelf(phiY);
    rotatedV2.rotateYSelf(phiY);
    rotatedV3.rotateYSelf(phiY);
    rotatedNorm.rotateYSelf(phiY);
}

const vec3f &Triangle::getRotatedV1() const {
    return rotatedV1;
}

const vec3f &Triangle::getRotatedV2() const {
    return rotatedV2;
}

const vec3f &Triangle::getRotatedV3() const {
    return rotatedV3;
}

const vec3f &Triangle::getRotatedNorm() const {
    return rotatedNorm;
}

const unreal_fluid::math::Angle &Triangle::getPhiY() const {
    return phiY;
}

const unreal_fluid::math::Angle &Triangle::getPhiZ() const {
    return phiZ;
}

const vec3f &Triangle::getV1() const {
    return v1;
}

const vec3f &Triangle::getV2() const {
    return v2;
}

const vec3f &Triangle::getV3() const {
    return v3;
}

const vec3f &Triangle::getNorm() const {
    return norm;
}
