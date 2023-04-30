/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SceneGLAdvanced.cxx
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

class SceneGLAdvanced : public Scene {
public:
  std::vector<render::RenderObject *> objs;
  std::vector<vec3f> positions;

  utils::Timer timer;

  explicit SceneGLAdvanced(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    for (int i = -20; i <= 20; i++) {
      for (int j = -50; j <= 0; j++) {
        render::mesh::Cube cubeMesh(0.5f);
        objs.push_back(new render::RenderObject{
          .bakedMesh = std::make_unique<render::mesh::BakedMesh>(&cubeMesh),
          .material = render::material::Lambertian(),
        });
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
        render::mesh::Cube cubeMesh(0.5f);
        objs.push_back(new render::RenderObject{
          .bakedMesh = std::make_unique<render::mesh::BakedMesh>(&cubeMesh),
          .material = render::material::Lambertian(),
        });
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
