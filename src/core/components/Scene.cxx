#include "Scene.h"

using namespace unreal_fluid;

void Scene::init() {
}

void Scene::update() {
  for (AbstractObject *object: objects) {
    object->update();
  }
}

void Scene::render() {
  for (AbstractObject *object: objects) {
    object->render();
  }
}

void Scene::clear() {
  for (AbstractObject *&object: objects) {
    delete &object;
    object = nullptr;
  }
}