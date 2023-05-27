/*
 * This is joke, so there is no copyright. Have fun :3
 * */

#include "../src/core/Core.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Cube.h"
#include "../src/core/render/components/mesh/presets/Plane.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

class d5a9fde3c505f2c80d6d548c3c9a93c5 : public Scene {
  std::vector<render::RenderObject *> rObjects;
  render::RenderObject *plane;
  utils::Timer timer;

public:
  d5a9fde3c505f2c80d6d548c3c9a93c5(const compositor::SceneCompositor * compositor) : Scene(compositor) {
    for (int i = 0; i < 10; i++) {
      render::mesh::Sphere sphereMesh(.2f, 50, 50);
      render::RenderObject *sphere = new render::RenderObject();
      // place in circle
      sphere->modelMatrix = mat4::translation({0, 2, -5}).withRotationZ(2 * M_PI * i / 10.f);
      sphere->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&sphereMesh);
      sphere->material = render::material::Lambertian();
      sphere->material.diffuseColor = {(rand() % 255) / 256.f, (rand() % 255) / 256.f, (rand() % 255) / 256.f};
      rObjects.push_back(sphere);
    }

    render::mesh::Plane planeMesh(9, 9, 10, 10, {0, 1, 0}, {1, 0, 0});
    plane = new render::RenderObject();
    plane->modelMatrix = mat4::translation({0, 0, 5});
    plane->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&planeMesh);
    plane->material = render::material::Lambertian();
    plane->textures[0] = new render::Texture("d5a9fde3c505f2c80d6d548c3c9a93c5.jpg");
    objects.push_back(new AbstractObject{nullptr, {plane}});
  }

  void update() override {
    Scene::update();

    static bool flag = true;

    float full_appear = 4.f;
    if (flag && objects.size() < 10.f) {
      int current_ball = (int) (timer.getElapsedTime() / full_appear * 10.f);

      current_ball = std::min(current_ball, 9);

      if (objects.size() <= current_ball)
        objects.push_back(new AbstractObject{nullptr, {rObjects[objects.size()]}});
    }

    static float current_rotation_speed = 0.f;
    static float current_speed = 0.f;
    static float z_current_speed = 0.f;
    static float current_pos = 0.f;
    static float z_current_pos = 0.f;

    float full_rotate = 4.f;
    if (flag && timer.getElapsedTime() > 1.2f && timer.getElapsedTime() < 1.2f + full_rotate) {
      current_rotation_speed += 0.0003;
    }

    if (flag && timer.getElapsedTime() > full_appear) {
      current_speed += 0.0001;
      current_pos += current_speed;
      if (current_pos > 2)
        z_current_speed += 0.001;
      z_current_pos += z_current_speed;
    }

    for (auto &object : rObjects) {
      object->modelMatrix *= mat4::rotationZ(current_rotation_speed);
      object->modelMatrix = mat4::translation({0, -current_speed, z_current_speed}) * object->modelMatrix;
    }

    if (flag && z_current_pos > 5) {
      flag = false;
      getRenderer()->camera.setDirection({0, 0});
      for (int i = 0; i < 9; i++) {
        objects.pop_back();
      }
    }
  }
};
