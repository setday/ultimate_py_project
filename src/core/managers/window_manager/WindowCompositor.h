/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : WindowCompositor.h
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : This is wrapper class for the glfw.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <iostream>
#include <functional>

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

    static std::vector<std::function<void(int key, int action)>> _keyboardCallbacks;
    static std::vector<std::function<void(int width, int height)>> _resizeCallbacks;

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
    [[nodiscard]] bool isAlive() const { return _isAlive; };

    /// General callback for the keyboard.
    /// @param window The window.
    /// @param key The key.
    /// @param scancode The scancode.
    /// @param action The action.
    /// @param mods The mods.
    static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// Add keyboard callback.
    /// @param callback The callback function.
    void addKeyboardCallback(const std::function<void(int key, int action)>& callback);

    /// General callback for the resize.
    /// @param window The window.
    /// @param width The width.
    /// @param height The height.
    static void resizeCallback(GLFWwindow* window, int width, int height);

    /// Add resize callback.
    /// @param callback The callback function.
    void addResizeCallback(const std::function<void(int width, int height)> &callback);

    /// Get size of the window.
    /// @param width The width of the window.
    /// @param height The height of the window.
    void getSize(int& width, int& height) const;
  }; // end of window_compositor class
} // end of unreal_fluid::window namespace

// end of WindowCompositor.h
