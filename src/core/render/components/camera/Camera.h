/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Camera.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::render {
  class Camera {
  private:
    vec3f _position  = {0.f, 0.f, 0.f};
    vec3f _direction = {0.f, 0.f, -1.f};
    vec3f _up        = {0.f, 1.f, 0.f};
    vec3f _right     = {1.f, 0.f, 0.f};

    float _height = 0.f;
    float _width  = 0.f;
    float _aspect = 1.f;

    float _fov    = 70.f;
    float _near   = 0.01f;
    float _far    = 1000.f;

    mat4 _view{};
    mat4 _projection{};

    vec3f _targetPosition      = {0.f, 0.f, 0.f};
    float _interpolationFactor = 0.f;
    utils::Timer _interpolationTimer;

    /// update view matrix
    void updateViewMatrix();

    /// update projection matrix
    void updateProjectionMatrix();

  public:
    Camera() = default;

    /// Constructor
    /// @param position - position of camera
    /// @param direction - direction of camera
    /// @param up - up vector of camera
    /// @param width - width of camera
    /// @param height - height of camera
    /// @param fov - field of view
    /// @param near - near plane
    /// @param far - far plane
    Camera(const vec3f &position, const vec3f &direction, const vec3f &up = {0.f, 1.f, 0.f},
           float width = 500.f, float height = 500.f,
           float fov = 70.f, float near = 0.01f, float far = 1000.0f);

    /// Get position of camera
    /// @return position of camera
    [[nodiscard]] vec3f getPosition() const;

    /// Set position of camera with interpolation
    /// @param position - position of camera
    /// @attention - interpolation is not working. You should use setPositionHard.
    void setPosition(const vec3f &position);

    /// Set position of camera without interpolation
    /// @param position - position of camera
    void setPositionHard(const vec3f &position);

    /// update camera position
    void updatePosition();

    /// Get direction of camera
    /// @return direction of camera
    [[nodiscard]] vec3f getDirection() const;

    /// Set direction of camera
    /// @param direction - direction of camera
    void setDirection(const vec3f &direction);

    // Set direction of camera
    /// @param yaw - yaw angle
    /// @param pitch - pitch angle
    void setDirection(float yaw, float pitch);

    /// Get resolution of camera
    /// @return resolution of camera
    [[nodiscard]] vec2f getResolution() const;

    /// Set camera resolution
    /// @param width - width of camera
    /// @param height - height of camera
    void setResolution(int width, int height);

    /// Get view matrix
    /// @return view matrix
    [[nodiscard]] mat4 getViewMatrix() const;

    /// Get projection matrix
    /// @return projection matrix
    [[nodiscard]] mat4 getProjectionMatrix() const;

    /// Get view with projection matrix
    /// @return view with projection matrix
    [[nodiscard]] mat4 getFullMatrix() const;

    /// Get right vector
    /// @return right vector
    [[nodiscard]] vec3f getRight() const;

    /// Get up vector
    /// @return up vector
    [[nodiscard]] vec3f getUp() const;
  };
} // unreal_fluid::render

// end of Camera.h
