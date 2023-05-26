/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GLTestScene.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Cube.h"
#include "../src/core/render/components/mesh/presets/Plane.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

class GlTestScene : public Scene {
public:
  render::RenderObject *sphere;
  render::RenderObject *plane;
  render::RenderObject *cube;
  render::RenderObject *triangle;

  utils::Timer timer;

  explicit GlTestScene(const compositor::SceneCompositor * compositor) : Scene(compositor) {
    render::mesh::Sphere sphereMesh(.5f, 50, 50);

    sphere = new render::RenderObject();
    sphere->modelMatrix = mat4::rotation(0.f, {0.f, 0.f, 1.f}).
                          withTranslation({-.75f, 0.f, -5.f});
    sphere->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&sphereMesh);
    sphere->material = render::material::Water();
    objects.push_back(new AbstractObject{nullptr, {sphere}});

    render::mesh::Plane planeMesh(300, 300, 50, 50);
    plane = new render::RenderObject();
    plane->modelMatrix = mat4::rotation(0.f, {0.f, 0.f, 1.f}).
                         withTranslation({0.f, -1.f, -5.f});
    plane->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&planeMesh);
    plane->material = render::material::CyanPlastic();
    objects.push_back(new AbstractObject{nullptr, {plane}});

    render::mesh::Cube cubeMesh(1.f);
    cube = new render::RenderObject();
    cube->modelMatrix = mat4::rotation(0.f, {0.f, 0.f, 1.f}).
                        withTranslation({.75f, 0.f, -5.f});
    cube->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&cubeMesh);
    cube->material = render::material::Ruby();
    objects.push_back(new AbstractObject{nullptr, {cube}});

    render::RenderObject *tree = new render::RenderObject("Lowpoly_tree_sample.obj");

    for (int i = 0; i < 250; i++) {
      vec3f position = {(rand() % 300 - 150) / 3.0f, -1, -5.f + (rand() % 300 - 150) / 3.0f};

      if (position.len2() < 100.0f) {
        i--;
        continue;
      }

      auto *object = new render::RenderObject();
      object->modelMatrix = mat4::rotation(rand() % 360, {0.f, 1.f, 0.f}).
                            withScale((rand() % 50 + 50) / 200.f).
                            withTranslation(position);
      object->bakedMesh = tree->bakedMesh;
      object->material = render::material::Ruby();

      objects.push_back(new AbstractObject{nullptr, {object}});
    }

    delete tree;
    tree = new render::RenderObject("lowpolytree.obj");

    for (int i = 0; i < 250; i++) {
      vec3f position = {(rand() % 300 - 150) / 3.0f, 1, -5.f + (rand() % 300 - 150) / 3.0f};

      if (position.len2() < 100.0f) {
        i--;
        continue;
      }


      auto *object = new render::RenderObject();
      object->modelMatrix = mat4::rotation(rand() % 360, {0.f, 1.f, 0.f}).
                            withScale((rand() % 50 + 50) / 50.f).
                            withTranslation(position);
      object->bakedMesh = tree->bakedMesh;
      object->material = render::material::Emerald();
      objects.push_back(new AbstractObject{nullptr, {object}});
    }

    delete tree;
  }

  void update() override {
    auto time = utils::Timer::getCurrentTimeAsDouble();

    sphere->modelMatrix =
            mat4::rotationY((float)std::sin(time / 10) * 100).
            withTranslation({-.75f, 0.f, -5.f});

    cube->modelMatrix =
            mat4::rotationY((float)-std::sin(time / 10) * 100).
            withTranslation({.75f, 0.f, -5.f});
  }

  ~GlTestScene() override = default;
};

// end of GLTestScene.cxx
