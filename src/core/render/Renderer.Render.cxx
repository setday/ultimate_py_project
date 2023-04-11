/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Renderer.Render.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::startFrame() {
  _objectsToRender.clear();

  _timer.resume();

  glEnable(GL_DEPTH_TEST);

  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} // end of Renderer::startFrame() function

void Renderer::bindCameraToShader(const ShaderProgram *shader) const {
  GLuint programID = shader->getId();

  /* Bind projection matrix */
  GLint projectionMatrixID = glGetUniformLocation(programID, "projectionMatrix");
  glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera.getProjectionMatrix().data());

  /* Bind camera data */
  GLint cameraID;
  cameraID = glGetUniformLocation(programID, "camera.position");
  glUniform3f(cameraID, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
  cameraID = glGetUniformLocation(programID, "camera.direction");
  glUniform3f(cameraID, camera.getDirection().x, camera.getDirection().y, camera.getDirection().z);
  cameraID = glGetUniformLocation(programID, "camera.up");
  glUniform3f(cameraID, 0.f, 1.f, 0.f);
}

void Renderer::bindObjectToShader(const ShaderProgram *shader, const RenderObject *object) const {
  GLuint programID = shader->getId();

  /* Bind model matrix */
  GLint modelMatrixID = glGetUniformLocation(programID, "modelMatrix");
  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, object->modelMatrix.data());

  /* Bind material data */
  GLint materialAmbientID = glGetUniformLocation(programID, "ambientColor");
  glUniform3f(materialAmbientID, object->material.ambientColor.x, object->material.ambientColor.y, object->material.ambientColor.z);
  GLint materialDiffuseID = glGetUniformLocation(programID, "diffuseColor");
  glUniform3f(materialDiffuseID, object->material.diffuseColor.x, object->material.diffuseColor.y, object->material.diffuseColor.z);
  GLint materialSpecularID = glGetUniformLocation(programID, "specularColor");
  glUniform3f(materialSpecularID, object->material.specularColor.x, object->material.specularColor.y, object->material.specularColor.z);
  GLint materialShininessID = glGetUniformLocation(programID, "shininess");
  glUniform1f(materialShininessID, object->material.shininess);


  /* Bind frame information */
  GLint frameID;
  frameID = glGetUniformLocation(programID, "frame.width");
  glUniform1i(frameID, camera.getResolution().x);
  frameID = glGetUniformLocation(programID, "frame.height");
  glUniform1i(frameID, camera.getResolution().y);
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
    bindObjectToShader(object->shaderProgram, object);

    drawVertexes(object->mesh.vertices, object->mesh.indices);
  }
}

void Renderer::drawRT() {
  DefaultShaderManager::GetRayTracingProgram()->activate();

  GLuint programID = DefaultShaderManager::GetRayTracingProgram()->getId();

  struct RayTracingVertex {
    mat4 modelMatrix;
    vec3f position;
    int meshType;
  };

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

  bindCameraToShader(DefaultShaderManager::GetRayTracingProgram());

  GLint objectsCountID;
  objectsCountID = glGetUniformLocation(programID, "objectCount");
  glUniform1i(objectsCountID, (int)(rtVertices.size()));

  glBindBuffer(GL_UNIFORM_BUFFER, _rtubo);
  glBindVertexArray(_fvao);
  glBindBuffer(GL_ARRAY_BUFFER, _fvbo);

  glBufferData(GL_UNIFORM_BUFFER, sizeof(RayTracingVertex) * rtVertices.size(), rtVertices.data(), GL_DYNAMIC_DRAW);
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

  GLint textureID;
  textureID = glGetUniformLocation(programID, "colorTexture");
  glUniform1i(textureID, 0);
  textureID = glGetUniformLocation(programID, "positionTexture");
  glUniform1i(textureID, 1);
  textureID = glGetUniformLocation(programID, "normalTexture");
  glUniform1i(textureID, 2);

  bindCameraToShader(DefaultShaderManager::GetPostProcessingProgram());

  glBindVertexArray(_fvao);
  glBindBuffer(GL_ARRAY_BUFFER, _fvbo);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Renderer::endFrame() {
  if (_renderMode == RenderMode::RAY_TRACING) {
    drawRT();
  }

  glDisable(GL_DEPTH_TEST);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glClear(GL_COLOR_BUFFER_BIT);

  //*
  postProcess();
  //*/

  /*
  glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, camera.getResolution().x, camera.getResolution().y, 0, 0, camera.getResolution().x, camera.getResolution().y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
   //*/

  glFinish();

  _timer.pause();
  _timer.incrementCounter();

  if (_timer.getCounter() >= 400) {
    Logger::logInfo("Rendering time: ", _timer.getAverageTime<utils::Timer::TimeType::MILLISECONDS>(), " ms");
    _timer.reset();
  }
} // end of Renderer::endFrame() function

// end of Renderer.Render.cxx
