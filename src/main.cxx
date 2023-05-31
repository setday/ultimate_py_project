/* Note: No copyright in this file because it is not a part of the project. */

#include <cmath>
#include "core/Core.h"
#include "core/physics/solid/mesh/SolidMesh.h"

void rotation(){
    double a = M_PI;
    LOG_INFO(std::cos(a), std::sin(a));
    LOG_INFO(std::cos(-a), std::sin(-a));
    unreal_fluid::physics::solid::Triangle t{{0.5, .1, 0}, {-0.5, 0, -0.5}, {-0.5, 0, 0.5}};
    LOG_INFO("Norm", t.norm);
    vec3f norm = t.norm;
    double phiY, phiZ;
    if (norm.x == 0 && norm.z == 0) {
        LOG_INFO("ok triangle");
        return;
    }
    phiY = std::acos(norm.x / sqrt(norm.x * norm.x + norm.z * norm.z));
    if (norm.z < 0) phiY = -phiY;
    t.v1.rotateYSelf(phiY);
    t.v2.rotateYSelf(phiY);
    t.v3.rotateYSelf(phiY);
    t.norm.rotateYSelf(phiY);
    LOG_INFO(phiY);
    LOG_INFO(t.v1, t.v2, t.v3, t.norm);
    assert(norm.z < 1e-2);
    phiZ = std::acos(norm.y / std::sqrt(norm.x * norm.x + norm.y * norm.y));
    if (norm.y < 0) phiZ = -phiZ;
    t.v1.rotateZSelf(phiZ);
    t.v2.rotateZSelf(phiZ);
    t.v3.rotateZSelf(phiZ);
    t.norm.rotateZSelf(phiZ);
    LOG_INFO(t.v1, t.v2, t.v3, t.norm);
}

int main() {
/*    vec3f v = {1, 1, 1};
    //v.rotateYSelf(-1);
    v.rotateZSelf(-1);
    LOG_INFO(v);*/
    //rotation();
    //return 0;
    unreal_fluid::Core core;
    core.run();
}

// end of main.cxx