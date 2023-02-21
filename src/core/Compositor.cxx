#include "Compositor.h"
#include "../scenes/CLTestScene.cxx"

using namespace unreal_fluid::compositor;

Compositor::Compositor() {
  //_windowCompositor = new window::WindowCompositor();
  _renderer = new render::Renderer();
  CLTestScene();
}

Compositor::~Compositor() {
  // delete _windowCompositor;
  delete _renderer;
}

void Compositor::init() {
  // _windowCompositor->init(500, 500);
  _renderer->init();
}

void Compositor::update() {
}

void Compositor::render() {
  // _renderer->renderObject(nullptr);
  // _windowCompositor->swapBuffers();
}

void Compositor::destroy() {
  _renderer->destroy();
  // _windowCompositor->destroy();
}