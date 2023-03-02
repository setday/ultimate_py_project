/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : WindowCompositor.h
 * PURPOSE   : This is wrapper class for the glfw.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

#include "../../../Definitions.h"

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

    /// Initializes the window compositor.
    /// @param width The width of the window.
    /// @param height The height of the window.
    void init(int width, int height);
    /// Method to draw opengl context to the screen.
    void update();
    /// Resizes the window.
    /// @param width The new width of the window.
    /// @param height The new height of the window.
    void resize(int width, int height);
    /// Destroys the window compositor.
    void destroy();

    /// Returns if the window compositor is alive.
    /// @return True if the window compositor is alive.</returns>
    bool isAlive() const { return _isAlive; };
  }; // end of window_compositor class
} // end of unreal_fluid::window namespace

// end of WindowCompositor.h
