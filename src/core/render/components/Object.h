#pragma once

#include "iostream"

namespace unreal_fluid::render {
    class Object {
    public:
        Object();

        ~Object();

        void update();

        void render();
    };
};