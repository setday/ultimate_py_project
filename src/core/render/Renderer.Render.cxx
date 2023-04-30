/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Renderer.Render.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::startFrame() {
  _objectsToRender.clear();

  glEnable(GL_DEPTH_TEST);

  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} // end of Renderer::startFrame() function

void Renderer::bindCameraToShader(const ShaderProgram *shader) const {
  /* Bind projection matrix */
  shader->bindUniformAttribute("projectionMatrix", camera.getProjectionMatrix());

  /* Bind camera data */
  shader->bindUniformAttribute("camera.position", camera.getPosition());
  shader->bindUniformAttribute("camera.direction", camera.getDirection());
  shader->bindUniformAttribute("camera.up", camera.getUp());

  /* Bind frame information */
  shader->bindUniformAttribute("frame.width", int(camera.getResolution().x));
  shader->bindUniformAttribute("frame.height", int(camera.getResolution().y));
}

void Renderer::drawVertexes(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

  glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Renderer::renderObjects(const std::vector<render::RenderObject *> &objects) {
  if (_renderMode == RenderMode::RAY_TRACING) {
    _objectsToRender.insert(_objectsToRender.end(), objects.begin(), objects.end());

    return;
  }

  for (const render::RenderObject *object : objects) {
    object->shaderProgram->activate();

    bindCameraToShader(object->shaderProgram);
    object->bindParametersToShader(object->shaderProgram);

    object->shaderProgram->bindUniformAttribute("time", float(_timer.getElapsedTime()));

    object->shaderProgram->bindUniformAttribute("isEmitter", object->isEmitter);

    glBindVertexArray(object->bakedMesh.get()->getVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->bakedMesh.get()->getIBO());
    glDrawElements(GL_TRIANGLE_STRIP, object->bakedMesh.get()->getIndicesCount(), GL_UNSIGNED_INT, 0);
  }
}

void Renderer::drawScreenQuad() const {
  glBindVertexArray(_fvao);
  glBindBuffer(GL_ARRAY_BUFFER, _fvbo);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Renderer::drawRT() {
  DefaultShaderManager::GetRayTracingProgram()->activate();

  GLuint programID = DefaultShaderManager::GetRayTracingProgram()->getId();

  struct RayTracingVertex {
    mat4 modelMatrix;
    vec3f position;
    int meshType;
  };

  /*
  std::vector<RayTracingVertex> rtVertices;
  for (auto object : _objectsToRender) {
    for (int i = 0; i < object->mesh.indices.size(); i++) {
      auto vertex = object->mesh.vertices[object->mesh.indices[i]];
      rtVertices.push_back({
                                   object->modelMatrix,
                                   vertex.position,
                                   object->mesh.meshType
                           });

      break;
    }
  }
   */

  bindCameraToShader(DefaultShaderManager::GetRayTracingProgram());

  GLint objectsCountID;
  objectsCountID = glGetUniformLocation(programID, "objectCount");
  // glUniform1i(objectsCountID, (int)(rtVertices.size()));

  glBindBuffer(GL_UNIFORM_BUFFER, _rtubo);
  glBindVertexArray(_fvao);
  glBindBuffer(GL_ARRAY_BUFFER, _fvbo);

  // glBufferData(GL_UNIFORM_BUFFER, sizeof(RayTracingVertex) * rtVertices.size(), rtVertices.data(), GL_DYNAMIC_DRAW);
  glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "ObjectDataBuffer"), 0);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, _rtubo);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Renderer::postProcess() {
  DefaultShaderManager::GetPostProcessingProgram()->activate();

  GLuint programID = DefaultShaderManager::GetPostProcessingProgram()->getId();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _fbto[1]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _fbto[2]);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, _fbto[3]);

  GLint textureID;
  textureID = glGetUniformLocation(programID, "colorTexture");
  glUniform1i(textureID, 0);
  textureID = glGetUniformLocation(programID, "positionTexture");
  glUniform1i(textureID, 1);
  textureID = glGetUniformLocation(programID, "normalTexture");
  glUniform1i(textureID, 2);

  bindCameraToShader(DefaultShaderManager::GetPostProcessingProgram());

  drawScreenQuad();
}

void Renderer::endFrame() {
  if (_renderMode == RenderMode::RAY_TRACING) {
    drawRT();
  }

  glDisable(GL_DEPTH_TEST);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glClear(GL_COLOR_BUFFER_BIT);

  postProcess();

  glFinish();
} // end of Renderer::endFrame() function

// end of Renderer.Render.cxx
