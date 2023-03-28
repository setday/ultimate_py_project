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
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"
#include "../src/core/render/components/mesh/presets/Plane.h"
#include "../src/core/render/components/mesh/presets/Cube.h"

using namespace unreal_fluid;

class GlTestScene : public Scene {
public:
  render::RenderObject *sphere;
  render::RenderObject *plane;
  render::RenderObject *cube;

  AbstractObject *object;

  utils::Timer timer;

  explicit GlTestScene(compositor::SceneCompositor const * compositor) : Scene(compositor) {
    sphere = new render::RenderObject();
    sphere->modelMatrix =
            mat4::rotation(0.f, {0.f, 0.f, 1.f}) *
            mat4::translation({-.75f, 0.f, -5.f});
    sphere->mesh = render::mesh::Sphere(.5f, 50, 50);
    sphere->material = render::material::MaterialFactory::createMaterial(
            render::material::MaterialFactory::MaterialType::WATTER
            );
    objects.push_back(new AbstractObject{nullptr, sphere});

    plane = new render::RenderObject();
    plane->mesh = render::mesh::Plane(300, 300, 50, 50);
    plane->modelMatrix =
            mat4::rotation(0.f, {0.f, 0.f, 1.f}) *
            mat4::translation({0.f, -1.f, -5.f});
    plane->material = render::material::MaterialFactory::createMaterial(
            render::material::MaterialFactory::MaterialType::CYAN_PLASTIC
            );
    objects.push_back(new AbstractObject{nullptr, plane});

    cube = new render::RenderObject();
    cube->mesh = render::mesh::Cube(.5f);
    cube->modelMatrix =
            mat4::rotation(0.f, {0.f, 0.f, 1.f}) *
            mat4::translation({.75f, 0.f, -5.f});
    cube->material = render::material::MaterialFactory::createMaterial(
            render::material::MaterialFactory::MaterialType::RUBY
            );
    objects.push_back(new AbstractObject{nullptr, cube});

    render::RenderObject *tree = new render::RenderObject();
    tree->loadFromFile("Lowpoly_tree_sample.obj");

    for (int i = 0; i < 250; i++) {
      vec3f position = {(rand() % 300 - 150) / 3.0f, -1, -5.f + (rand() % 300 - 150) / 3.0f};

      if (position.len2() < 100.0f) {
        i--;
        continue;
      }

      render::RenderObject *object = new render::RenderObject();
      object->mesh = tree->mesh;
      object->modelMatrix =
              mat4::rotation(rand() % 360, {0.f, 1.f, 0.f}) *
              mat4::scale((rand() % 50 + 50) / 200.f) *
              mat4::translation(position);
      object->material = render::material::MaterialFactory::createMaterial(
              render::material::MaterialFactory::MaterialType::RUBY
              );
      objects.push_back(new AbstractObject{nullptr, object});
    }

    delete tree;
    tree = new render::RenderObject();
    tree->loadFromFile("lowpolytree.obj");

    for (int i = 0; i < 250; i++) {
      vec3f position = {(rand() % 300 - 150) / 3.0f, 1, -5.f + (rand() % 300 - 150) / 3.0f};

      if (position.len2() < 100.0f) {
        i--;
        continue;
      }

      render::RenderObject *object = new render::RenderObject();
      object->mesh = tree->mesh;
      object->modelMatrix =
              mat4::rotation(rand() % 360, {0.f, 1.f, 0.f}) *
              mat4::scale((rand() % 50 + 50) / 50.f) *
              mat4::translation(position);
      object->material = render::material::MaterialFactory::createMaterial(
              render::material::MaterialFactory::MaterialType::EMERALD
      );
      objects.push_back(new AbstractObject{nullptr, object});
    }

    delete tree;
  }

  void update() override {
    auto time = utils::Timer::getCurrentTimeAsDouble();

    sphere->modelMatrix =
            mat4::rotationY(std::sin(time / 10) * 100) *
            mat4::translation({-.75f, 0.f, -5.f});

    cube->modelMatrix =
            mat4::rotationY(-std::sin(time / 10) * 100) *
            mat4::translation({.75f, 0.f, -5.f});
  }

  ~GlTestScene() override = default;
};

// end of GLTestScene.cxx
