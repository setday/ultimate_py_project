#include "Scene.h"


namespace unreal_fluid::render {

    void Scene::init() {

    }

    void Scene::update() {
        for (auto & object : objects) {
            object.update();
        }
    }

    void Scene::render() {
        for (auto & object : objects) {
            object.render();
        }
    }

    void Scene::clear() {

    }
} // namespace unreal_fluid::render
