#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::Init() const {
  Logger::log(Logger::Level::INFO, "Initializing renderer...");

  InitGl();

  Logger::log(Logger::Level::INFO, "Renderer initialized!");
} // end of Renderer::Renderer() function

void Renderer::InitGl() const {
  // initialize viewport and ect
  glViewport(0, 0, 500, 500);

  glClearColor(0.05f, 0.05f, 0.1f, 0.0f);
  glClearDepth(1.0f);

  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // load camera matrix
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enable alpha test
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.1f);

  // enable texture 2d
  glEnable(GL_TEXTURE_2D);

  // enable culling
  glEnable(GL_CULL_FACE);
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
  glLoadIdentity();
  glRotatef(object->zAxisAngle, 0.f, 0.f, 1.f);

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < object->vertices.size(); i++) {
    glColor3f(object->colors[i][0], object->colors[i][1], object->colors[i][2]);
    glVertex3f(object->vertices[i][0], object->vertices[i][1], object->vertices[i][2]);
  }
  glEnd();
} // end of Renderer::renderObject() function

void Renderer::Destroy() const {
  glDisable(GL_DEPTH_TEST);
} // end of Renderer::destroy() function
