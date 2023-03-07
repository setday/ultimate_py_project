#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::Init() {
  Logger::logInfo("Initializing renderer...");

  _shaderManager = new ShaderManager();

  camera = Camera(vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f),
                  vec3f(0.0f, 0.0f, -1.0f), 1.0f, 45.0f, 0.01f, 1000.0f);

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
  glLoadMatrixf((
          camera.getProjectionMatrix() * object->modelMatrix
          ).withTranspose().data());

  vec2f viewportSize = camera.getResolution();
  glViewport(0, 0, viewportSize.x, viewportSize.y);

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < object->mesh.indices.size(); i++) {
    auto vertex = object->mesh.vertices[object->mesh.indices[i]];
    glColor4f(vertex.color.x, vertex.color.y, vertex.color.z, 1.f);
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

// end of Renderer.cxx
