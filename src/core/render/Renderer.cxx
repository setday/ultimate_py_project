#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::Init() {
  Logger::logInfo("Initializing renderer...");

  _shaderManager = new ShaderManager();

  camera = Camera(vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 0.0f, 1.0f),
                  vec3f(0.0f, 1.0f, 0.0f), 1.0f, 45.0f, 0.01f, 1000.0f);

  InitGl();

  float frameVertices[] = {
      -1.0f, -1.0f, 0.0f,0.0f, 0.0f,
      1.0f,  -1.0f, 0.0f,1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      1.0f,  1.0f, 0.0f, 1.0f, 1.0f
  };

  glGenVertexArrays(1, &_fvao);
  glGenBuffers(1, &_fvbo);

  glBindVertexArray(_fvao);
  glBindBuffer(GL_ARRAY_BUFFER, _fvbo);

  glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), frameVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ibo);

  glGenBuffers(1, &_rtubo);

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

void Renderer::StartFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _objectsToRender.clear();
} // end of Renderer::startFrame() function

void Renderer::RenderObject(const render::RenderObject *object) {
  if (_renderMode == RenderMode::RAY_TRACING) {
    _objectsToRender.push_back(object);

    return;
  }

  object->shaderProgram->Execute();

  GLuint programID = object->shaderProgram->GetProgramID();

  GLuint projectionMatrixID = glGetUniformLocation(programID, "projectionMatrix");
  glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera.getProjectionMatrix().data());
  GLuint modelMatrixID = glGetUniformLocation(programID, "modelMatrix");
  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, object->modelMatrix.data());

  GLuint cameraID;
  cameraID = glGetUniformLocation(programID, "camera.position");
  glUniform3f(cameraID, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
  cameraID = glGetUniformLocation(programID, "camera.direction");
  glUniform3f(cameraID, camera.getDirection().x, camera.getDirection().y, camera.getDirection().z);
  cameraID = glGetUniformLocation(programID, "camera.up");
  glUniform3f(cameraID, 0.f, 1.f, 0.f);

  // send material data
  GLuint materialAmbientID = glGetUniformLocation(programID, "ambientColor");
  glUniform3f(materialAmbientID, object->material.ambient_color.x, object->material.ambient_color.y, object->material.ambient_color.z);
  GLuint materialDiffuseID = glGetUniformLocation(programID, "diffuseColor");
  glUniform3f(materialDiffuseID, object->material.diffuse_color.x, object->material.diffuse_color.y, object->material.diffuse_color.z);
  GLuint materialSpecularID = glGetUniformLocation(programID, "specularColor");
  glUniform3f(materialSpecularID, object->material.specular_color.x, object->material.specular_color.y, object->material.specular_color.z);
  GLuint materialShininessID = glGetUniformLocation(programID, "shininess");
  glUniform1f(materialShininessID, object->material.shininess);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

  glBufferData(GL_ARRAY_BUFFER, object->mesh.vertices.size() * sizeof(Vertex), object->mesh.vertices.data(), GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->mesh.indices.size() * sizeof(unsigned int), object->mesh.indices.data(), GL_DYNAMIC_DRAW);

  glDrawElements(GL_TRIANGLES, object->mesh.indices.size(), GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
} // end of Renderer::renderObject() function

void Renderer::RenderAllObjects(const std::vector<render::RenderObject *> &objects) {
  for (auto object : objects) {
    RenderObject(object);
  }
}

void Renderer::EndFrame() {
  if (_renderMode == RenderMode::RAY_TRACING) {
    _shaderManager->GetRayTracingProgram()->Execute();

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
      }
    }

    glBindVertexArray(_fvao);
    glBindBuffer(GL_ARRAY_BUFFER, _fvbo);
    glBindBuffer(GL_UNIFORM_BUFFER, _rtubo);

    GLuint rtProgramID = _shaderManager->GetRayTracingProgram()->GetProgramID();
    glBufferData(GL_UNIFORM_BUFFER, sizeof(RayTracingVertex) * rtVertices.size(), rtVertices.data(), GL_DYNAMIC_DRAW);
    glUniformBlockBinding(rtProgramID, glGetUniformBlockIndex(rtProgramID, "ObjectDataBuffer"), 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, _rtubo);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  glFinish();
} // end of Renderer::endFrame() function

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
