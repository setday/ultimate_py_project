/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AbstractObject.h"
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"
#include "../physics/solid/sphere/SolidSphere.h"

using namespace unreal_fluid;

AbstractObject::AbstractObject(physics::IPhysicalObject* physObject) {
    physicalObject = physObject;
}

void AbstractObject::parse() {
  physics::IPhysicalObject::Type type = physicalObject->getType();
  void *data = physicalObject->getData();
  if (type == physics::IPhysicalObject::Type::SIMPLE_FLUID_CONTAINER) {
    std::vector<physics::fluid::Particle *> &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(data);
    for (int pos = 0; pos < particles.size(); ++pos) {
      if (pos >= renderObjects.size()) {
        renderObjects.push_back(new render::RenderObject);
        renderObjects.back()->material = render::material::MaterialFactory::createMaterial(
                render::material::MaterialFactory::MaterialType::GOLD
        );
      }
      auto &particle = particles[pos];
      auto &renderObject = renderObjects[pos];
      ///TODO dynamic sphere quality should be used. The large the radius, the higher the quality is
      if (renderObject->mesh.indices.empty()) {
        renderObject->mesh = render::mesh::Sphere((float) particle->radius, 15, 15);
      } ///TODO less complex to check whether the mesh is empty should be used
      renderObject->position = particle->position;
      renderObject->modelMatrix = mat4::translation(renderObject->position);
    }
  }else if (type == physics::IPhysicalObject::Type::SOLID_SPHERE){
      Logger::logInfo("starting");
      if (renderObjects.empty()){
          renderObjects.push_back(new render::RenderObject);
      }
      auto solidSphere = reinterpret_cast<physics::solid::SolidSphere*>(data);
      if (renderObjects[0]->mesh.indices.empty()) {
          renderObjects[0]->mesh = render::mesh::Sphere((float)solidSphere->getRadius(), 50, 50);
      }
      renderObjects[0]->position = solidSphere->getPosition();
      renderObjects[0]->modelMatrix = mat4::translation(renderObjects[0]->position);
      Logger::logInfo("completed");
  }
}

[[nodiscard]] std::vector<render::RenderObject *> &AbstractObject::getRenderObjects() {
  return renderObjects;
}

[[nodiscard]] physics::IPhysicalObject *AbstractObject::getPhysicalObject() {
  return physicalObject;
}
