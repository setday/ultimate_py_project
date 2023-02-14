#pragma once
#include <iostream>

#include "Core.h"

using namespace unreal_fluid;

Core::Core() {
  run() {
    while (_isRunning) {
      _compositor.update();
      _compositor.render();
    }
  };
  init() {
    _isRunning = true;
    _compositor.init();
  };
  shutdown() {
    _isRunning = false;
    _compositor.destroy();
  };
  std::cout << "Core::Core()" << std::endl;
} // end of Core::Core() function
