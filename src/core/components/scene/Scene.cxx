/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Scene.cxx
 * PURPOSE   : Class that realizes update of advanced scene.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Scene.h"

using namespace unreal_fluid;

Scene::Scene(compositor::SceneCompositor const *compositor) {
  this->compositor = compositor;
}

void Scene::update() {
  PhysicalScene::update();
}

void Scene::render() {
  RenderScene::render();
}

[[nodiscard]] render::Renderer *Scene::getRenderer() const {
  return compositor->getRenderer();
}

[[nodiscard]] Core *Scene::getCore() const {
  return compositor->getCore();
}

// end of Scene.cxx
