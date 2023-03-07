#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::Init() {
  Logger::logInfo("Initializing renderer...");

  _shaderManager = new ShaderManager();

  camera = Camera(vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 0.0f, 1.0f),
                  vec3f(0.0f, 1.0f, 0.0f), 1.0f, 45.0f, 0.01f, 1000.0f);

  InitGl();

  ChangeRenderMode(RenderMode::SOLID);

  Logger::logInfo("Renderer initialized!");
} // end of Renderer::Renderer() function

void Renderer::InitGl() const {
  // initialize viewport and ect
  glViewport(0, 0, 500, 500);

  glClearColor(0.05f, 0.05f, 0.1f, 0.0f);
  glClearDepth(1.0f);

  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enable alpha test
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.1f);

  // enable texture 2d
  glEnable(GL_TEXTURE_2D);

  // set culling
  glCullFace(GL_BACK);

  // enable point smoothing
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
} // end of Renderer::initGL() function

void Renderer::StartFrame() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
} // end of Renderer::startFrame() function

void Renderer::RenderObject(const render::RenderObject *object) const {
  glMatrixMode(GL_MODELVIEW);

  GLuint projectionMatrixID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "projectionMatrix");
  glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera.getProjectionMatrix().data());
  GLuint modelMatrixID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "modelMatrix");
  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, object->modelMatrix.data());

  GLuint cameraPositionID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "cameraPosition");
  glUniform3f(cameraPositionID, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
  GLuint cameraDirectionID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "cameraDirection");
  glUniform3f(cameraDirectionID, camera.getDirection().x, camera.getDirection().y, camera.getDirection().z);
  GLuint cameraUpID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "cameraUp");
  glUniform3f(cameraUpID, 0.f, 1.f, 0.f);

  // send material data
  GLuint materialAmbientID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "ambientColor");
  glUniform3f(materialAmbientID, object->material.ambient_color.x, object->material.ambient_color.y, object->material.ambient_color.z);
  GLuint materialDiffuseID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "diffuseColor");
  glUniform3f(materialDiffuseID, object->material.diffuse_color.x, object->material.diffuse_color.y, object->material.diffuse_color.z);
  GLuint materialSpecularID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "specularColor");
  glUniform3f(materialSpecularID, object->material.specular_color.x, object->material.specular_color.y, object->material.specular_color.z);
  GLuint materialShininessID = glGetUniformLocation(object->shaderProgram->GetProgramID(), "shininess");
  glUniform1f(materialShininessID, object->material.shininess);

  object->shaderProgram->Execute();

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < object->mesh.indices.size(); i++) {
    auto vertex = object->mesh.vertices[object->mesh.indices[i]];
    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
    glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
  }
  glEnd();
} // end of Renderer::renderObject() function

void Renderer::Destroy() {
  glDisable(GL_DEPTH_TEST);

  delete _shaderManager;
} // end of Renderer::destroy() function

ShaderManager *Renderer::GetShaderManager() const {
  return _shaderManager;
} // end of Renderer::getShaderManager() function

void Renderer::ChangeRenderMode(RenderMode mode) {
  _renderMode = mode;

  if (mode == RenderMode::WIREFRAME) {
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else if (mode == RenderMode::SOLID) {
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
  } else if (mode == RenderMode::TEXTURED) {
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
} // end of Renderer::changeRenderMode() function

void Renderer::changeResolution(int width, int height) {
  camera.setResolution(width, height);

  glViewport(0, 0, width, height);
}

// end of Renderer.cxx
