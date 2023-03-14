#include "Scene.h"

using namespace unreal_fluid;

void Scene::Init() {
  // The base realization doesn't need to initialize resources
}

void Scene::Update() {
  double dt = 0.2; // TODO what a fuck is going on with dt time
  for (AbstractObject *object: objects) {
    object->update(dt);
  }
}

void Scene::Render() {
  for (AbstractObject *object: objects) {
    object->render();
  }
}

void Scene::Clear() {
  for (AbstractObject *&object: objects) {
    delete &object;
  }
}