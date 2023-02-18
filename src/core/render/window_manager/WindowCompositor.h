//
// Copyright (c) 2023 Unreal Fluid. All rights reserved.
//

#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

namespace unreal_fluid::window {
  /// <summary>
  /// Wrapper class for the window compositor.
  /// This class is responsible for creating and destroying the window.
  /// It also handles the swap-buffers to draw opengl context to the screen.
  /// </summary>
  class WindowCompositor {
  private:
    bool _isAlive = false;
    GLFWwindow* _window = nullptr;
    int _width = 0;
    int _height = 0;

  public:
    WindowCompositor();
    ~WindowCompositor();

    /// <summary>
    /// Initializes the window compositor.
    /// @param width The width of the window.
    /// @param height The height of the window.
    /// </summary>
    void init(int width, int height);
    /// <summary>
    /// Method to draw opengl context to the screen.
    /// </summary>
    void swapBuffers();
    /// <summary>
    /// Resizes the window.
    /// @param width The new width of the window.
    /// @param height The new height of the window.
    /// </summary>
    void resize(int width, int height);
    /// <summary>
    /// Destroys the window compositor.
    /// </summary>
    void destroy();
  }; // end of window_compositor class
} // end of unreal_fluid::window namespace
