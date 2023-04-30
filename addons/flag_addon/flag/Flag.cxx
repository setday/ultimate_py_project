/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid Flag Addon
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : Flag.cxx
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "Flag.h"

using namespace unreal_fluid::addons::physics;

Flag::Flag(double width, double height, int widthSegments, int heightSegments) : _widthSegments(widthSegments),
                                                                                 _heightSegments(heightSegments) {
  double widthStep = width / widthSegments;
  double heightStep = height / heightSegments;

  for (int i = 0; i < widthSegments; ++i) {
    for (int j = 0; j < heightSegments; ++j) {
      _points.emplace_back(vec3(i * widthStep, 0, j * heightStep));
    }
  }

  for (int i = 0; i < widthSegments; ++i) {
    for (int j = 0; j < heightSegments; ++j) {
      if (i < widthSegments - 1) {
        _constraints.emplace_back(
                &_points[i * heightSegments + j],
                &_points[(i + 1) * heightSegments + j],
                1, 0.1, widthStep
                );
      }
      if (j < heightSegments - 1) {
        _constraints.emplace_back(
                &_points[i * heightSegments + j],
                &_points[i * heightSegments + j + 1],
                1, 0.1, heightStep
                );
      }
      /*if (i < widthSegments - 1 && j < heightSegments - 1) {
        _constraints.emplace_back(
                &_points[i * heightSegments + j],
                &_points[(i + 1) * heightSegments + j + 1],
                1, 0.1, sqrt(widthStep * widthStep + heightStep * heightStep)
                );
      }
      if (i < widthSegments - 1 && j < heightSegments - 1) {
        _constraints.emplace_back(
                &_points[(i + 1) * heightSegments + j],
                &_points[i * heightSegments + j + 1],
                1, 0.1, sqrt(widthStep * widthStep + heightStep * heightStep)
                );
      }*/
    }
  }
}

void Flag::update(double dt) {
  for (auto &constraint : _constraints) {
    constraint.update();
  }

  for (auto &point : _points) {
    point.update(dt);
  }
}

// end of Flag.cxx
