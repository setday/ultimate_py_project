#include "Scene.h"

using namespace unreal_fluid;

void Scene::init() {
  // The base realization doesn't need to initialize resources
}

void Scene::update() {
  // The base realization doesn't need to update resources
}

void Scene::render() {
  // The base realization doesn't need to render resources
}

void Scene::clear() {
  for (AbstractObject *&object: objects) {
    delete &object;
  }
}