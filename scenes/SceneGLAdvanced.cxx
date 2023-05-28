/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : SceneGLAdvanced.cxx
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Cube.h"
using namespace unreal_fluid;

class SceneGLAdvanced : public Scene {
public:
  std::vector<render::RenderObject *> objs;
  std::vector<vec3f> positions;
  render::RenderObject *cube;

  utils::Timer timer;

  explicit SceneGLAdvanced(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    render::mesh::Cube cubeMesh(1.f);

    cube = new render::RenderObject();
    cube->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&cubeMesh);
    cube->material = render::material::Lambertian();
    cube->textures[0] = new render::Texture("dubai_2023.jpg");
    objects.push_back(new AbstractObject(nullptr, {cube}));

    for (int i = -20; i <= 20; i++) {
      for (int j = -50; j <= 0; j++) {
        auto *object = new render::RenderObject();
        object->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&cubeMesh);
        object->material = render::material::Lambertian();
        objs.push_back(object);

        positions.emplace_back(i * 1.1f, -1.7f + (rand() % 10) / 15.f, j * 1.1f);
        if (rand() % 40 == 0) {
          objs.back()->isEmitter = true;
          if (rand() % 2 == 0) {
            objs.back()->material.diffuseColor = {1.0, 0, 1.0};
          } else {
            objs.back()->material.diffuseColor = {0, 1.0, 1.0};
          }
        }
        objects.push_back(new AbstractObject(nullptr, {objs.back()}));
      }
    }

    for (int i = -20; i <= 20; i++) {
      for (int j = -50; j <= 0; j++) {
        auto *object = new render::RenderObject();
        object->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&cubeMesh);
        object->material = render::material::Lambertian();
        objs.push_back(object);

        positions.emplace_back(i * 1.1f, 1.7f + (rand() % 10) / 15.f, j * 1.1f);
        objects.push_back(new AbstractObject(nullptr, {objs.back()}));
      }
    }
  }

  void update() override {
    getRenderer()->camera.setUp({
      float(sin(timer.getElapsedTime() / 3) * 0.2f + 0.1f),
      1,
      0
    });

    cube->modelMatrix = mat4::rotationY(timer.getElapsedTime() / 2) * mat4::translation({0, 0, -6.f});

    for (int i = 0; i < objs.size(); i++) {
      positions[i].z += 0.1f;
      if (positions[i].z > 0) {
        positions[i].z = -55.f;
      }
      vec3f pos = positions[i];
      pos.y += sin(pos.x + pos.z) * 0.1f;
      objs[i]->modelMatrix = mat4::translation(pos);
    }
  }
};

// end of SceneGLAdvanced.cxx
