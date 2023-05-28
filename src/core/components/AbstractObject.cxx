/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 * PURPOSE   : Abstract object to store render and physical objects in one
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AbstractObject.h"
#include "../physics/solid/mesh//Plane.h"
#include "../physics/solid/mesh/SolidMesh.h"
#include "../physics/solid/sphere/SolidSphere.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Plane.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject, const std::vector<render::RenderObject *> &renderObjects) : physicalObject(physicalObject),
                                                                                                                                     renderObjects(renderObjects) {}

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) : physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)) {}

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject) : physicalObject(physicalObject) {}

void AbstractObject::parse() {
  if (physicalObject == nullptr) return;

  auto type = physicalObject->getType();
  void *data = physicalObject->getData();

  if (type == physics::IPhysicalObject::Type::FLUID_CONTAINER_SIMPLE ||
      type == physics::IPhysicalObject::Type::FLUID_CONTAINER_ADVANCED) {

    auto &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(data);

    for (int pos = 0; pos < particles.size(); ++pos) {

      if (pos >= renderObjects.size()) {

        auto renderObject = new render::RenderObject;
        renderObject->material = render::material::Water();
        if (type == physics::IPhysicalObject::Type::FLUID_CONTAINER_SIMPLE) {
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
  } else if (type == physics::IPhysicalObject::Type::SOLID_SPHERE) {

    auto solidSphere = *static_cast<physics::solid::SolidSphere *>(data);

    if (renderObjects.empty()) {

      auto renderObject = new render::RenderObject;

      renderObject->material = render::material::Bronze();
      auto r = solidSphere.radius;
      auto mesh = render::mesh::Sphere(float(r), unsigned(500 * r), unsigned(500 * r));
      renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
      renderObjects.push_back(renderObject);
    }

    renderObjects.back()->modelMatrix = mat4::translation(solidSphere.position);

  } else if (type == physics::IPhysicalObject::Type::SOLID_MESH) {

    auto &triangles = *static_cast<std::vector<physics::solid::Triangle> *>(data);

    for (size_t pos = renderObjects.size(); pos < triangles.size(); ++pos) {
      const auto &triangle = triangles[pos];
      auto renderObject = new render::RenderObject();
      auto mesh = render::mesh::BasicMesh({triangle.v1, triangle.v2, triangle.v3}, {0, 1, 2});
      renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
      renderObject->material = render::material::GreenPlastic();
      renderObjects.push_back(renderObject);
    }
  } else if (type == physics::IPhysicalObject::Type::SOLID_PLANE) {

    auto plane = *static_cast<physics::solid::Plane *>(data);

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
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}

// end of AbstractObject.cxx
