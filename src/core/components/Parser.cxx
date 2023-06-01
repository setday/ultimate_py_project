/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Parser.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Parser.h"
#include "../physics/fluid/Particle.h"
#include "../physics/solid/mesh/Plane.h"
#include "../physics/solid/mesh/Mesh.h"
#include "../physics/solid/sphere/Sphere.h"
#include "../render/components/mesh/presets/Plane.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid::physics;

void Parser::parsePlane(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects) {
  auto plane = *static_cast<solid::Plane *>(object.getData());

  if (renderObjects.empty()) {
    auto renderObject = new render::RenderObject;
    renderObject->material = render::material::Ruby();
    renderObject->material.diffuseColor = {0.08627f, 0.819607f, 0.20392f};
    auto mesh = render::mesh::Plane(plane.width, plane.height);
    renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
    renderObjects.push_back(renderObject);
  }

  renderObjects.back()->modelMatrix = mat4::translation(plane.position);
}

void Parser::parseSphere(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects) {
  auto solidSphere = *static_cast<solid::Sphere *>(object.getData());

  if (renderObjects.empty()) {
    auto renderObject = new render::RenderObject;
    renderObject->material = render::material::Bronze();
    auto r = solidSphere.radius;
    auto mesh = render::mesh::Sphere(r, unsigned(500 * r), unsigned(500 * r));
    renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
    renderObjects.push_back(renderObject);
  }

  renderObjects.back()->modelMatrix = mat4::translation(solidSphere.position);
}

void Parser::parseMesh(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects) {
  auto &triangles = *static_cast<std::vector<solid::Triangle> *>(object.getData());

  for (size_t pos = renderObjects.size(); pos < triangles.size(); ++pos) {
    const auto &triangle = triangles[pos];
    auto renderObject = new render::RenderObject();
    auto mesh = render::mesh::BasicMesh({triangle.getV1(), triangle.getV2(), triangle.getV3()}, {0, 1, 2});
    renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
    renderObject->material = render::material::GreenPlastic();
    renderObjects.push_back(renderObject);
  }
}

void Parser::parseContainer(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects) {
  auto &particles = *static_cast<std::vector<fluid::Particle *> *>(object.getData());

  for (int pos = 0; pos < particles.size(); ++pos) {

    if (pos >= renderObjects.size()) {

      auto renderObject = new render::RenderObject;
      renderObject->material = render::material::Water();
      if (object.getType() == unreal_fluid::physics::IPhysicalObject::Type::FLUID_CONTAINER_SIMPLE){
          renderObject->material.ambientColor.x = 0.2f;
          renderObject->material.diffuseColor.x = 0.2f;
      }
      auto r = particles[pos]->radius;
      auto mesh = render::mesh::Sphere(float(r), 10, 10);
      renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
      renderObjects.push_back(renderObject);
    }
    renderObjects[pos]->modelMatrix = mat4::translation(particles[pos]->position);
  }
}

std::vector<solid::Triangle> Parser::parseRenderMesh(const render::mesh::BasicMesh &mesh) {
  std::vector<solid::Triangle> triangles;
  triangles.reserve(mesh.indices.size());
  for (int pos = 0; pos + 2 < mesh.indices.size(); ++pos) {
    if (mesh.indices[pos] == RESET_INDEX) continue;
    triangles.emplace_back(mesh.vertices[pos].position, mesh.vertices[pos + 1].position, mesh.vertices[pos + 2].position);
  }
  return triangles;
}
