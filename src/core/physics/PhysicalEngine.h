#pragma once
#include "fluid/fluid1/Fluid1Container.h"

namespace unreal_fluid::fluid{
  class PhysicalEngine {
  private:
    std::vector<Fluid1Container> fluids1;
  public:
    PhysicalEngine() = default;
    ~PhysicalEngine() = default;
    void simulate(double dt);
    //void createFluid1(fluidDescriptor);
  };
}

