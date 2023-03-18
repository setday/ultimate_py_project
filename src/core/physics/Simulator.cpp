#include "Simulator.h"


void unreal_fluid::physics::Simulator::addPhysObject(unreal_fluid::physics::PhysObject *physObject) {
    physObjects.push_back(physObject);
}

void unreal_fluid::physics::Simulator::simulate(double dt) {
    //TODO simulate solids and fluids
    for (auto & physObject : physObjects) {
        physObject->simulate(dt);
    }
}

void unreal_fluid::physics::Simulator::clearData() {
    physObjects.clear();
}
