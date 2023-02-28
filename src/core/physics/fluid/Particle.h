#pragma once
#include "../../maths/MathHeaders"

using namespace unreal_fluid;

namespace unreal_fluid::fluid {
  class Particle {
  private:
    math::Vector3<double> _velocity, _position;
    double _radius, _mass;

  public:
    void *metaData;

  public:
    double getX() const;
    double getY() const;
    double getZ() const;
    double radius() const;
    void advect(double dt);
    Particle(const vec3 &velocity, const vec3 &position, double radius, double mass, void *metaData);
    ~Particle() = default;
  };
} // namespace unreal_fluid::fluid
