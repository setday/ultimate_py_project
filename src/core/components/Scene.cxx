#include "Scene.h"

using namespace unreal_fluid;

void Scene::Init() {
  // The base realization doesn't need to initialize resources
}

void Scene::Update() {
  double dt = 0.2; /// TODO what is going on with dt time?
  for (AbstractObject *object: objects) {
    object->update(dt);
  }
}

void Scene::Clear() {
  for (AbstractObject *&object: objects) {
    delete &object;
  }
}