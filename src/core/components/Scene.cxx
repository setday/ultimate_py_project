#include "Scene.h"

using namespace unreal_fluid;

void Scene::Init() {
  // The base realization doesn't need to initialize resources
}

void Scene::Update() {
  for (AbstractObject const *object: objects) {
    object->Update();
  }
}

void Scene::Render() {
  for (AbstractObject const *object: objects) {
    object->Render();
  }
}

void Scene::Clear() {
  for (AbstractObject *&object: objects) {
    delete &object;
  }
}