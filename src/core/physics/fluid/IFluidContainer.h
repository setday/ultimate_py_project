#pragma once
#include "../../maths/MainMath.h"
#include "Particle.h"
#include "vector"

namespace unreal_fluid::fluid {
  class IFluidContainer {

  public:
    IFluidContainer() = delete;
    virtual ~IFluidContainer() = default;

    virtual void simulate(double dt) = 0;

    virtual const std::vector<Particle> *getParticles() = 0;
  };
} // namespace unreal_fluid::fluid
