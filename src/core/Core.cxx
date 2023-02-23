#include <iostream>

#include "Core.h"

using namespace unreal_fluid;

Core::Core() : _compositor(this) {
}

Core::~Core() = default;

void Core::Run() {
  Init();

  while (_isRunning) {
    Update();
  }

  Shutdown();
}

void Core::Init() {
  _isRunning = true;
  _compositor.Init();
}

void Core::Update() {
  _compositor.Update();
  _compositor.Render();
}

void Core::Shutdown() {
  _compositor.Destroy();
  _isRunning = false;
}
