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
    //LOG_INFO("ROTATING");
    //LOG_INFO("PhiY", phiY);
    p.position.rotateYSelf(phiY);
    p.velocity.rotateYSelf(phiY);
    triangle.v1.rotateYSelf(phiY);
    triangle.v2.rotateYSelf(phiY);
    triangle.v3.rotateYSelf(phiY);
    triangle.norm.rotateYSelf(phiY);
    vec3f norm = triangle.norm;
    //assert(norm.z < 1e-4);
    double phiZ = std::acos(norm.y / std::sqrt(norm.x * norm.x + norm.y * norm.y));
    if (norm.z < 0) phiZ = -phiZ;
    //phiZ = 2;
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
    //LOG_INFO("ROTATED BACK");
}

#define LOG_INFO(...) ;

void CollisionSolver::particleWithTriangleCollision(fluid::Particle *p, solid::Triangle *triangle, double k) {
    //LOG_INFO("Before:", p->position, triangle->v1, triangle->v2, triangle->v3);
    auto norm = vec3f(triangle->norm);//delete
    double phiY = 0, phiZ = 0;
    if (!(norm.x == 0 && norm.z == 0)) {
        double cos = norm.x / sqrt(norm.x * norm.x + norm.z * norm.z);
       // LOG_INFO("cos:", cos);
        if (cos > 1){
            phiY = 0;
        } else if (cos < -1){
            phiY = M_PI;// TODO inaccuracy hazard
        }else{
            phiY = std::acos(cos);
        }
        //LOG_INFO(phiY);
        if (norm.y < 0) phiY = -phiY;
        //phiY = 1;
        phiZ = rotate(phiY, *p, *triangle);
    }

    //LOG_INFO("Rotated:", phiY, phiZ);
    double dist = p->position.y - triangle->v1.y;
    if (abs(dist) < p->radius) {
        LOG_INFO("distance check passed:", dist, p->radius);
        math::Line2D s1 = {{triangle->v1.x, triangle->v1.z},
                           {triangle->v2.x, triangle->v2.z}};
        math::Line2D s2 = {{triangle->v2.x, triangle->v2.z},
                           {triangle->v3.x, triangle->v3.z}};
        math::Line2D s3 = {{triangle->v3.x, triangle->v3.z},
                           {triangle->v1.x, triangle->v1.z}};
        math::Line2D scanBeam({p->position.x, p->position.z}, {100'000, 100'000});
        int countIntersections = 0;
        LOG_INFO("Scan beam:", scanBeam.p1, scanBeam.p2);
        countIntersections += (s1.intersectSegmentWithSegment(scanBeam) != LINE2D_NULL_POINT);
        LOG_INFO(countIntersections, s1.p1, s1.p2);
        countIntersections += (s2.intersectSegmentWithSegment(scanBeam) != LINE2D_NULL_POINT);
        LOG_INFO(countIntersections, s2.p1, s2.p2);
        countIntersections += (s3.intersectSegmentWithSegment(scanBeam) != LINE2D_NULL_POINT);
        LOG_INFO(countIntersections, s3.p1, s3.p2);
        if (countIntersections % 2 != 0) {
            LOG_INFO("internal check passed");
            double push = p->radius - abs(dist);
            if (dist < 0) push = -push;
            p->position.y += push;
            p->velocity.y *= -k;
        } else {
            LOG_INFO("Checking edge collision");
            if (edgeCollide(p, triangle->v1, triangle->v2, k)) {
                LOG_INFO("col1");
            } else if (edgeCollide(p, triangle->v2, triangle->v3, k)) {
                LOG_INFO("col2");
            } else if (edgeCollide(p, triangle->v1, triangle->v3, k)) {
                LOG_INFO("col3");
            } else {
                LOG_INFO("Have not collided");
            }
        }
        LOG_INFO("//////////////////////////////////////////////////////////////////////////");
        //LOG_FATAL(0);
    }
    if (!(phiZ == 0 && phiY == 0))
        rotateBack(-phiY, -phiZ, *p, *triangle);
    //LOG_INFO("After:", p->position, triangle->v1, triangle->v2, triangle->v3);
}

bool CollisionSolver::edgeCollide(fluid::Particle *p, vec3f p1, vec3f p2, double k) {
    LOG_INFO("Starting collide check");
    auto directionVector = (p2 - p1).normalize();
    LOG_INFO("points", p1, p2);
    vec3f particleProjection = ((vec3f) (p->position) - p1).project(directionVector) * directionVector +
                               p1;//math::Vector3<float>::project(p->position - p1, directionVector) * directionVector + p1;
    LOG_INFO("proj:", particleProjection);
    double segmentLen1 = (particleProjection - p1).len(), segmentLen2 = (particleProjection - p2).len();
    if (segmentLen1 + segmentLen2 > (p2 - p1).len()) {
        if (segmentLen1 < segmentLen2) particleProjection = p1;
        else
            particleProjection = p2;
    }
    vec3f dist = (p->position - particleProjection);
    LOG_INFO("Dist to particle:", dist);
    double length = dist.len();

    if (length == 0) {
        LOG_INFO("CollisionSolver::edgeCollide p,position on segment");
        return false;
    }
    LOG_INFO("length and radius:", length, p->radius);
    if (length > p->radius) {
        LOG_INFO("Edge collision failed");
        return false;
    }

    dist /= length;

    p->position += (p->radius - length) * dist;
    vec3f velocityProjection = dist * math::Vector3<float>::project(p->velocity, dist);
    p->velocity -= (1 - k) * velocityProjection;
    return true;
}

// end of CollisionSolver.cxx