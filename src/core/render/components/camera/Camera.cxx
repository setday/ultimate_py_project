/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Camera.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Camera.h"

using namespace unreal_fluid::render;

void Camera::updateViewMatrix() {
  return;
  _view = mat4::lookAt(_position, _position + _direction, _up);
}

void Camera::updateProjectionMatrix() {
  _projection = mat4::perspective(_fov, _aspect, _near, _far);
}

Camera::Camera(const vec3f &position, const vec3f &direction, const vec3f &up, float aspect, float fov, float near,
               float far) : _position(position), _direction(direction), _up(up), _fov(fov), _near(near), _far(far),
                            _aspect(aspect), _height(500.f), _width(500.f), _view(), _projection() {
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

void Camera::setDirection(const vec3f &direction) {
  _direction = direction;
  updateViewMatrix();
}

void Camera::setDirection(float yaw, float pitch) {
  _direction.z = cos(yaw) * cos(pitch);
  _direction.y = sin(pitch);
  _direction.x = sin(yaw) * cos(pitch);
  updateViewMatrix();
}

vec2f Camera::getResolution() const {
  return vec2f(_width, _height);
}

void Camera::setResolution(int width, int height) {
  _width = width;
  _height = height;
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

// end of Camera.cxx
