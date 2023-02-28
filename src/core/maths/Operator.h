#pragma once
#include "cmath"

namespace unreal_fluid::math {

    template<typename T>
    double inverseSqrt(T x) {
        //TODO make pure double sqrt calculation
        auto temp = static_cast<float>(x);
        int i = *(int*)&temp;
        i = 0x5f3759df - (i >> 1);
        float y = *(float*)&i;
        y *= (1.5F - 0.5F * x * y * y);
        y *= (1.5F - 0.5F * x * y * y);
        return y * (1.5F - 0.5F * x * y * y);
    }

    const double G = 9.81;

} // namespace maths
