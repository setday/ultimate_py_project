#include "Scene.h"

using namespace unreal_fluid;

void Scene::Init() {
  // The base realization doesn't need to initialize resources
}

void Scene::Clear() {
  for (AbstractObject *&object: objects) {
    delete &object;
  }
}