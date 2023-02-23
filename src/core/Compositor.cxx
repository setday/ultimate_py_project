#include "Compositor.h"
#include "../scenes/ClTestScene.cxx"

using namespace unreal_fluid::compositor;

Compositor::Compositor(Core *core) : _core(core) {
  //_windowCompositor = new window::WindowCompositor();
  _renderer = new render::Renderer();
}

Compositor::~Compositor() {
  // delete _windowCompositor;
  delete _renderer;
}

void Compositor::Init() {
  // _windowCompositor->init(500, 500);
  _renderer->Init();
  ClTestScene(this);
}

void Compositor::Update() {
}

void Compositor::Render() {
  // _renderer->renderObject(nullptr);
  // _windowCompositor->swapBuffers();
}

void Compositor::Destroy() {
  _renderer->Destroy();
  // _windowCompositor->destroy();
}

Core *Compositor::GetCore() const {
  return _core;
}
