/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Camera.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include <cmath>

#include "Camera.h"

using namespace unreal_fluid::render;

void Camera::updateViewMatrix() {
  return;
  _view = mat4::lookAt(_position, _position + _direction, _up);
}

void Camera::updateProjectionMatrix() {
  _projection = mat4::perspective(_fov, _aspect, _near, _far);
}

Camera::Camera(const vec3f &position, const vec3f &direction, const vec3f &up,
               float width, float height,
               float fov, float near, float far) :
        _position(position), _direction(direction.normalize()), _up(up.normalize()),
        _right(direction.cross(up).normalize()),
        _height(height), _width(width), _aspect(width / height),
        _fov(fov), _near(near), _far(far) {
  setDirection(direction);

  updateViewMatrix();
  updateProjectionMatrix();
}

vec3f Camera::getPosition() const {
  return _position;
}

void Camera::setPosition(const vec3f &position) {
  _targetPosition = position;
  _interpolationFactor = 0.f;
  _interpolationTimer.reset();
}

void Camera::setPositionHard(const vec3f &position) {
  _targetPosition = _position = position;
  updateViewMatrix();
}

void Camera::updatePosition() {
  _interpolationFactor += 0.1f;

  if (_interpolationFactor < 1.f) {
    _position = _position.lerped(_targetPosition, _interpolationFactor);
    updateViewMatrix();
  } else {
    _position = _targetPosition;
  }
}

vec3f Camera::getDirection() const {
  return _direction;
}

vec2f Camera::getAngles() const {
  return {_pitch, _yaw};
}

void Camera::setDirection(const vec3f &direction) {
  _direction = direction.normalize();

  _right = _direction.cross(_up).normalize();

  _pitch = float(asin(_direction.y));
  _yaw = float(atan2(_direction.x, _direction.z));

  updateViewMatrix();
}

void Camera::setDirection(const vec2f &angles) {
  _pitch = angles.x;
  _yaw = angles.y;

  _direction.z = std::cos(_yaw) * std::cos(_pitch);
  _direction.y = std::sin(_pitch);
  _direction.x = std::sin(_yaw) * std::cos(_pitch);

  _right = _direction.cross(_up).normalize();

  updateViewMatrix();
}

vec2f Camera::getResolution() const {
  return {_width, _height};
}

void Camera::setResolution(int width, int height) {
  _width = float(width);
  _height = float(height);
  _aspect = _width / _height;
  updateProjectionMatrix();
}

mat4 Camera::getViewMatrix() const {
  return _view;
}

mat4 Camera::getProjectionMatrix() const {
  return _projection;
}

mat4 Camera::getFullMatrix() const {
  return _view * _projection;
}

vec3f Camera::getRight() const {
  return _right;
}

vec3f Camera::getUp() const {
  return _up;
}

void Camera::setUp(const vec3f &up) {
  _up = up.normalize();

  _right = _direction.cross(_up).normalize();

  updateViewMatrix();
}

// end of Camera.cxx
