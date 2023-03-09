#include "PhysicalEngine.h"

using unreal_fluid::fluid::PhysicalEngine;

void PhysicalEngine::simulate(double dt) {
  for (int i = 0; i < fluids1.size(); ++i) {
    fluids1[i].simulate(dt);
  }
  //TODO solids and fluids, fluid -> solid, solid and gas.
}

//createSomething functions.