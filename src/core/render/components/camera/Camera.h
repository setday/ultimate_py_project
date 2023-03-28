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
    vec3f _position;
    vec3f _direction;
    vec3f _up;
    vec3f _right;

    float _fov;
    float _aspect;
    float _near;
    float _far;

    float _height;
    float _width;

    mat4 _view;
    mat4 _projection;

    vec3f _targetPosition;
    float _interpolationFactor;
    utils::Timer _interpolationTimer;

  private:
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
    /// @param aspect - aspect ratio
    /// @param fov - field of view
    /// @param near - near plane
    /// @param far - far plane
    Camera(const vec3f &position, const vec3f &direction, const vec3f &up, float aspect, float fov = 45.f,
           float near = 0.01f, float far = 1000.0f);

    /// Get position of camera
    /// @return position of camera
    vec3f getPosition() const;

    /// Set position of camera with interpolation
    /// @param position - position of camera
    void setPosition(const vec3f &position);

    /// Set position of camera without interpolation
    /// @param position - position of camera
    void setPositionHard(const vec3f &position);

    /// update camera position
    void updatePosition();

    /// Get direction of camera
    /// @return direction of camera
    vec3f getDirection() const;

    /// Set direction of camera
    /// @param direction - direction of camera
    void setDirection(const vec3f &direction);

    // Set direction of camera
    /// @param yaw - yaw angle
    /// @param pitch - pitch angle
    void setDirection(float yaw, float pitch);

    /// Get resolution of camera
    /// @return resolution of camera
    vec2f getResolution() const;

    /// Set camera resolution
    /// @param width - width of camera
    /// @param height - height of camera
    void setResolution(int width, int height);

    /// Get view matrix
    /// @return view matrix
    mat4 getViewMatrix() const;

    /// Get projection matrix
    /// @return projection matrix
    mat4 getProjectionMatrix() const;

    /// Get view with projection matrix
    /// @return view with projection matrix
    mat4 getFullMatrix() const;
  };
} // unreal_fluid::render

// end of Camera.h
