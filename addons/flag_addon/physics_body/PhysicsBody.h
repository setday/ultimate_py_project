/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : PhysicsBody.h
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "./../../../src/Definitions.h"

namespace unreal_fluid::addons::physics {
  struct PhysicsBody {
    vec3 position{0.0f, 0.0f, 0.0f};
    vec3 velocity{0.0f, 0.0f, 0.0f};
    vec3 acceleration{0.0f, 0.0f, 0.0f};

    vec3 rotation{0.0f, 0.0f, 0.0f};
    vec3 angularVelocity{0.0f, 0.0f, 0.0f};
    vec3 angularAcceleration{0.0f, 0.0f, 0.0f};

    double mass = 1.0f;
    double inverseMass = 1.0f;

    bool isStatic = false;

//    mat4 inertiaTensor{1.0f, 0.0f, 0.0f, 0.0f,
//                       0.0f, 1.0f, 0.0f, 0.0f,
//                       0.0f, 0.0f, 1.0f, 0.0f,
//                       0.0f, 0.0f, 0.0f, 0.0f};

    std::vector<vec3> vertices;

    PhysicsBody() = default;

    /// @brief Constructor of Point PhysicsBody
    /// @param point Point
    /// @param mass Mass
    /// @attention If mass is -1 then the body is static
    PhysicsBody(vec3 point, double mass = 1) : position(point), mass(mass),
                                               inverseMass(1.0f / mass), isStatic(mass == -1) {}

    /// @brief Applies force to the body
    /// @param force Force
    /// @param point Point of application
    void applyForce(const vec3 &force, const vec3 &point = {0.0f, 0.0f, 0.0f});

    /// @brief Applies impulse to the body
    /// @param impulse Impulse
    /// @param point Point of application
    void applyImpulse(const vec3 &impulse, const vec3 &point = {0.0f, 0.0f, 0.0f});

    /// @brief Applies torque to the body
    /// @param torque Torque
    void applyTorque(const vec3 &torque);

    /// @brief Applies angular impulse to the body
    /// @param angularImpulse Angular impulse
    void applyAngularImpulse(const vec3 &angularImpulse);


    /// @brief Updates position and rotation of the body
    /// @param dt Time interval
    void update(double dt);
  };
} // unreal_fluid::addons::physics

// end of PhysicsBody.h
