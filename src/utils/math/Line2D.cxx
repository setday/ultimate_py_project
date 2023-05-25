/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : UnrealFluidPhysics
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : Line2D.cxx
* PURPOSE   :
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#include "Line2D.h"
#include <cassert>
using namespace unreal_fluid::math;

Line2D::Line2D(vec2 p1, vec2 p2) {
  this->p1 = {p1.x, p1.y, 0};
  this->p2 = {p2.x, p2.y, 0};
  //TODO bug hazard
  a = p2.y - p1.y;
  b = p1.x - p2.x;
  c = p2.x * p1.y - p1.x * p2.y;
  if (b == 0) {
    //TODO process this case
    LOG_WARNING("b = 0 from Line2D");
  } else {
    k = -a / b;
    m = -c / b;
  }
}

vec3f Line2D::intersectLineWithLine(Line2D l) {
  //TODO bug hazard
  if (k != l.k) {
    float px = (l.m - m) / (k - l.k);
    float py = (k * px + m) / (k - l.k);
    return {px, py, 0};
  }
  if (m == l.m)
    return LINE2D_NULL_POINT;
  return p1;
}

vec3f Line2D::intersectSegmentWithSegment(Line2D l) {
  auto pIntersect1 = intersectSegmentWithLine(l);
  auto pIntersect2 = l.intersectSegmentWithLine(*this);
  if (pIntersect1 == LINE2D_NULL_POINT || pIntersect2 == LINE2D_NULL_POINT) {
    return LINE2D_NULL_POINT;
  }
  assert(pIntersect1 == pIntersect2);
  return pIntersect1;
}

vec3f Line2D::intersectSegmentWithLine(Line2D l) {
  vec3f p = intersectLineWithLine(l);
  if (distanceSegmentToPoint(p) < ACCURACY)
    return p;
  return LINE2D_NULL_POINT;
}

float Line2D::distanceLineToPoint(vec3f p) {
  //TODO bug hazard
  float d = std::abs((a * p.x + b * p.y + c) / std::sqrt(a * a + b * b));
  if (d < ACCURACY) return 0;
  return d;
}

float Line2D::distanceSegmentToPoint(vec3f p) {
  //TODO bug hazard
  vec3f paral = (p2 - p1).normalize();
  float pProj = p.project(paral);
  float p1Proj = p1.project(paral);
  float p2Proj = p2.project(paral);
  if (p1Proj > p2Proj) std::swap(p1Proj, p2Proj);
  if (p1Proj <= pProj && pProj <= p2Proj)
    return distanceLineToPoint(p);
  return std::min(p1.distanceTo(p), p2.distanceTo(p));
}