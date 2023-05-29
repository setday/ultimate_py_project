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
#include "../physics/solid/mesh/SolidMesh.h"
#include "../physics/solid/sphere/SolidSphere.h"
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
  auto solidSphere = *static_cast<solid::SolidSphere *>(object.getData());

  if (renderObjects.empty()) {
    auto renderObject = new render::RenderObject;
    renderObject->material = render::material::Bronze();
    auto r = solidSphere.radius;
    auto mesh = render::mesh::Sphere(float(r), unsigned(500 * r), unsigned(500 * r));
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
    auto mesh = render::mesh::BasicMesh({triangle.v1, triangle.v2, triangle.v3}, {0, 1, 2});
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
      renderObject->material.ambientColor.x = 0.2f;
      renderObject->material.diffuseColor.x = 0.2f;
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
  triangles.reserve(mesh.vertices.size());
  for (auto vertex: mesh.vertices) {
    triangles.emplace_back(vertex.position, vertex.position, vertex.position);
    /// TODO : convert position to tree points
  }
  return triangles;
}
