#include "Renderer.h"

using namespace unreal_fluid::render;

void Renderer::Init() const {
  InitGl();
} // end of Renderer::Renderer() function

void Renderer::InitGl() const {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // made RGBA frame mode
} // end of Renderer::initGL() function

void Renderer::RenderObject(const render::RenderObject *object) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glEnd();
} // end of Renderer::renderObject() function

void Renderer::Destroy() const {
  glDisable(GL_DEPTH_TEST);
} // end of Renderer::destroy() function
