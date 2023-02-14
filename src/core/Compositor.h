#pragma once

namespace unreal_fluid::compositor {
  class Compositor {

  public:
    Compositor();
    ~Compositor();

    void init();
    void update();
    void render();
    void destroy();
  }; // compositor class
} // compositor
