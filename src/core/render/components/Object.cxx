#include "Object.h"

namespace unreal_fluid::render {
    Object::Object() {
        std::cout << "Object()";
    }

    Object::~Object() {
        std::cout << "~Object()";
    }

    void Object::update() {
        std::cout << "update()";
    }

    void Object::render() {
        std::cout << "render()";
    }
} // namespace unreal_fluid::render
