/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CollisionSolver.cxx
 * PURPOSE   : Implements collision between different objects
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "CollisionSolver.h"

using namespace unreal_fluid::physics;

void CollisionSolver::particleWithParticleCollision(fluid::Particle *p1, fluid::Particle *p2, double k) {
  vec3 diff = p1->position - p2->position;

  if (diff.len2() == 0) return;

  double diffLen = diff.len();
  vec3 direction = diff / diffLen;

  double pushValue =
          (p1->radius + p2->radius - diffLen) /
          (p1->mass + p2->mass);

  if (pushValue < 0) return;

  vec3 pushVector = direction * pushValue;

  p1->position += pushVector * p2->mass;
  p2->position -= pushVector * p1->mass;

  double momentumValue =
          (1 - k) *
          (p1->velocity.dot(direction) - p2->velocity.dot(direction)) /
          (p1->mass + p2->mass);
  vec3 momentum = direction * momentumValue;

  p1->velocity -= momentum * p2->mass;
  p2->velocity += momentum * p1->mass;
}

void CollisionSolver::particleWithSphereCollision(fluid::Particle *p, solid::SolidSphere *s, double k) {
  vec3 diff = s->position - p->position;

  if (diff.len2() == 0) return;

  double diffLen = diff.len();

  if (diffLen > p->radius + s->radius) return;

  diff /= diffLen;

  double pushValue = s->radius + p->radius - diffLen;

  p->position -= diff * pushValue;
  p->velocity -= diff * (1 - k) * p->velocity.dot(diff);
}

void CollisionSolver::particleWithPlaneCollision(fluid::Particle *particle, solid::Plane *plane, double k) {
  vec3 diff = particle->position - plane->position;
  double newYPos = diff.dot(plane->normal);
  double newXPos = diff.dot(plane->right);
  double newZPos = diff.dot(plane->front);
  double pushNormal = newYPos - particle->radius;

  if (abs(newYPos) >= particle->radius + 0.02 || abs(newXPos) > plane->width / 2 ||
      abs(newZPos) > plane->height / 2)
    return;

  double normalVelocityValue = particle->velocity.dot(plane->normal);
  if (normalVelocityValue == 0) return;

  double pushCoefficient = pushNormal / normalVelocityValue + 0.0002;

  particle->position -= pushCoefficient * particle->velocity;

  vec3 normalVelocity = normalVelocityValue * plane->normal;

  particle->velocity -= 2 * normalVelocity;
  particle->velocity *= (1 - k);
}

double CollisionSolver::rotate(double phiY, fluid::Particle &p, solid::Triangle &triangle) {
  p.position.rotateYSelf(phiY);
  p.velocity.rotateYSelf(phiY);
  triangle.v1.rotateYSelf(phiY);
  triangle.v2.rotateYSelf(phiY);
  triangle.v3.rotateYSelf(phiY);
  triangle.norm.rotateYSelf(phiY);
  vec3f norm = triangle.norm;
  //assert(norm.z < 1e-4);
  double phiZ;
  if (norm.x == 0 && norm.y == 0) phiZ = 0;
  else
    phiZ = std::acos(norm.y / std::sqrt(norm.x * norm.x + norm.y * norm.y));
  if (norm.z < 0) phiZ = -phiZ;
  p.position.rotateZSelf(phiZ);
  p.velocity.rotateZSelf(phiZ);
  triangle.v1.rotateZSelf(phiZ);
  triangle.v2.rotateZSelf(phiZ);
  triangle.v3.rotateZSelf(phiZ);
  triangle.norm.rotateZSelf(phiZ);
  return phiZ;
}

void CollisionSolver::rotateBack(double phiY, double phiZ, fluid::Particle &p, solid::Triangle &triangle) {
  p.position.rotateZSelf(phiZ);
  p.velocity.rotateZSelf(phiZ);
  triangle.v1.rotateZSelf(phiZ);
  triangle.v2.rotateZSelf(phiZ);
  triangle.v3.rotateZSelf(phiZ);
  triangle.norm.rotateZSelf(phiZ);
  p.position.rotateYSelf(phiY);
  p.velocity.rotateYSelf(phiY);
  triangle.v1.rotateYSelf(phiY);
  triangle.v2.rotateYSelf(phiY);
  triangle.v3.rotateYSelf(phiY);
  triangle.norm.rotateYSelf(phiY);
}

void CollisionSolver::particleWithTriangleCollision(fluid::Particle *p, solid::Triangle *triangle, double k) {
  double phiY;
  if (!(triangle->norm.x == 0 && triangle->norm.z == 0))
    phiY = std::acos(triangle->norm.x / sqrt(triangle->norm.x * triangle->norm.x + triangle->norm.z * triangle->norm.z));
  else
    phiY = 0;
  if (triangle->norm.y < 0) phiY = -phiY;
  double phiZ = rotate(phiY, *p, *triangle);
  double dist = p->position.y - triangle->v1.y;
  Logger::logDebug(dist, p->radius);
  if (abs(dist) < p->radius) {
//    math::Line2D s1 = {{triangle->v1.x, triangle->v1.z}, {triangle->v2.x, triangle->v2.z}};
//    math::Line2D s2 = {{triangle->v2.x, triangle->v2.z}, {triangle->v3.x, triangle->v3.z}};
//    math::Line2D s3 = {{triangle->v3.x, triangle->v3.z}, {triangle->v1.x, triangle->v1.z}};
//    math::Line2D scanBeam({p->position.x, p->position.z}, {100'000, 100'000});
//    int countIntersections = 0;
//    countIntersections += (s1.intersectSegmentWithSegment(scanBeam) != LINE2D_NULL_POINT);
//    countIntersections += (s2.intersectSegmentWithSegment(scanBeam) != LINE2D_NULL_POINT);
//    countIntersections += (s3.intersectSegmentWithSegment(scanBeam) != LINE2D_NULL_POINT);
//    if (countIntersections % 2 != 0) {
      double push = p->radius - abs(dist);
      if (dist < 0) push = -push;
      Logger::logDebug("before", p->position.y);
      p->position.y += push;
      Logger::logDebug("after", p->position.y);
      p->velocity.y *= -k;
//    } else {
//      if (edgeCollide(p, triangle->v1, triangle->v2, k) ||
//          edgeCollide(p, triangle->v2, triangle->v3, k) ||
//          edgeCollide(p, triangle->v1, triangle->v3, k)) {};
//    }
  }
  rotateBack(-phiY, -phiZ, *p, *triangle);
}

bool CollisionSolver::edgeCollide(fluid::Particle *p, vec3f p1, vec3f p2, double k) {
  auto directionVector = (p2 - p1).normalize();
  vec3f particleProjection = math::Vector3<float>::project(p->position - p1, directionVector) * directionVector + p1;
  double segmentLen1 = (particleProjection - p1).len();
  double segmentLen2 = (particleProjection - p2).len();
  if (segmentLen1 + segmentLen2 > (p2 - p1).len()) {
    if (segmentLen1 < segmentLen2) particleProjection = p1;
    else
      particleProjection = p2;
  }
  vec3f dist = p->position - particleProjection;
  double length = dist.len();
  if (length == 0) {
    LOG_INFO("CollisionSolver::edgeCollide p,position on segment");
    return false;
  }
  if (length > p->radius) return false;
  dist /= length;

  p->position += (p->radius - length) * dist;
  vec3f velocityProjection = dist * math::Vector3<float>::project(p->velocity, dist);
  p->velocity -= (1 - k) * velocityProjection;
  return true;
}

// end of CollisionSolver.cxx