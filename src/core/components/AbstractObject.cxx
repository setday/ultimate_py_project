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
#include "../physics/solid/mesh/SolidMesh.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject,
                               const std::vector<render::RenderObject *> &renderObjects) :
                               physicalObject(physicalObject), renderObjects(renderObjects) {}

AbstractObject::AbstractObject(physics::fluid::FluidDescriptor descriptor) :
                               physicalObject(new physics::fluid::SimpleFluidContainer(descriptor)) {}

AbstractObject::AbstractObject(physics::IPhysicalObject *physicalObject) :
                               physicalObject(physicalObject) {}

void AbstractObject::parse() {
  if (physicalObject == nullptr) {
    return;
  }

  auto type = physicalObject->getType();
  void *data = physicalObject->getData();

  if (type == physics::IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER) {

    auto &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(data);

    for (int pos = 0; pos < particles.size(); ++pos) {

      if (pos >= renderObjects.size()) {
        auto r = particles[pos]->radius;
        render::mesh::Sphere sphere(float(r), unsigned(500 * r), unsigned(500 * r));

        auto *renderObject = new render::RenderObject();
        renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&sphere);
        renderObject->material = render::material::Gold();
        renderObjects.push_back(renderObject);
      }

      renderObjects[pos]->modelMatrix = mat4::translation(particles[pos]->position);
    }
  } else if (type == physics::IPhysicalObject::Type::SOLID_SPHERE) {

    auto solidSphere = *static_cast<physics::solid::SolidSphere *>(data);

    if (renderObjects.empty()) {
      auto r = solidSphere.radius;
      render::mesh::Sphere sphere(float(r), unsigned(500 * r), unsigned(500 * r));

      auto *renderObject = new render::RenderObject();
      renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&sphere);
      renderObject->material = render::material::Bronze();
      renderObjects.push_back(renderObject);
    }

    renderObjects.back()->modelMatrix = mat4::translation(solidSphere.position);

  } else if (type == physics::IPhysicalObject::Type::SOLID_MESH) {

    auto &triangles = *static_cast<std::vector<physics::solid::Triangle> *>(data);

    for (size_t pos = renderObjects.size(); pos < triangles.size(); ++pos) {
      auto const& triangle = triangles[pos];
      render::mesh::BasicMesh mesh({triangle.v1, triangle.v2, triangle.v3}, {0, 1, 2});

      auto *renderObject = new render::RenderObject();
      renderObject->bakedMesh = std::make_unique<render::mesh::BakedMesh>(&mesh);
      renderObject->material = render::material::GreenPlastic();
      renderObjects.push_back(renderObject);

      if (pos == 0)
        renderObjects.back()->material = render::material::Gold();
      else if (pos == 1)
        renderObjects.back()->material = render::material::RedPlastic();
    }
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}

// end of AbstractObject.cxx
