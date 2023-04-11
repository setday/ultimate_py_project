/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Renderer.Main.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Renderer.h"

using namespace unreal_fluid::render;

void GLAPIENTRY openglDebugInfo(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
  Logger::logInfo("---------------------opengl-callback-start------------");
  Logger::logInfo("message:", message);

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      Logger::logInfo("type: ERROR");
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      Logger::logInfo("type: DEPRECATED_BEHAVIOR");
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      Logger::logInfo("type: UNDEFINED_BEHAVIOR");
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      Logger::logInfo("type: PORTABILITY");
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      Logger::logInfo("type: PERFORMANCE");
      break;
    case GL_DEBUG_TYPE_OTHER:
      Logger::logInfo("type: OTHER");
      break;
  }

  Logger::logInfo("id:", id);
  switch (severity){
    case GL_DEBUG_SEVERITY_LOW:
      Logger::logInfo("severity: LOW");
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      Logger::logInfo("severity: MEDIUM");
      break;
    case GL_DEBUG_SEVERITY_HIGH:
      Logger::logInfo("severity: HIGH");
      break;
  }

  Logger::logInfo("---------------------opengl-callback-end--------------");
}

Renderer::Renderer() {
  Logger::logInfo("Initializing renderer...");

  glewInit();

  _shaderManager = std::make_unique<ShaderManager>();

  camera = Camera(vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 0.0f, -1.0f),
                  vec3f(0.0f, 1.0f, 0.0f), 1.0f, 70.0f, 0.01f, 1000.0f);

  initGl();
  initBuffers();

  changeRenderMode(RenderMode::SOLID);

  _timer.pause();
  _timer.reset();

  Logger::logInfo("Renderer initialized!");
} // end of Renderer::Renderer() function

void Renderer::initGl() const {
  /*
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(openglDebugInfo, nullptr);
  //*/

  // initialize viewport and ect
  glViewport(0, 0, 500, 500);

  glClearColor(0.05f, 0.05f, 0.1f, 0.0f);
  glClearDepth(1.0f);


  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(RESET_INDEX);

  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  // glShadeModel(GL_SMOOTH);

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enable alpha test
  // glEnable(GL_ALPHA_TEST);
  // glAlphaFunc(GL_GREATER, 0.1f);

  // enable texture 2d
  glEnable(GL_TEXTURE_2D);

  // set culling
  glCullFace(GL_BACK);

  // enable point smoothing
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
} // end of Renderer::initGL() function

void Renderer::initBuffers() {
  float frameVertices[] = {
          -1.0f, -1.0f, 0.0f,0.0f, 0.0f,
          1.0f,  -1.0f, 0.0f,1.0f, 0.0f,
          -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
          1.0f,  1.0f, 0.0f, 1.0f, 1.0f
  };

  glGenVertexArrays(1, &_fvao);
  glGenBuffers(1, &_fvbo);

  glBindVertexArray(_fvao);
  glBindBuffer(GL_ARRAY_BUFFER, _fvbo);

  glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), frameVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ibo);

  glGenBuffers(1, &_rtubo);

  // FBO
  glGenTextures(6, _fbto);

  // depth
  glBindTexture(GL_TEXTURE_2D, _fbto[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 500, 500, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  // result color
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _fbto[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 500, 500, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glGenerateMipmap(GL_TEXTURE_2D);

  for (int i = 2; i < 6; i++) {
    glActiveTexture(GL_TEXTURE0 + i - 1);
    glBindTexture(GL_TEXTURE_2D, _fbto[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 500, 500, 0, GL_RGBA, GL_FLOAT, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  glGenFramebuffers(1, &_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _fbto[0], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fbto[1], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _fbto[2], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _fbto[3], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, _fbto[4], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, _fbto[5], 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // check framebuffer status
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE) {
    Logger::logError("Framebuffer is not complete:", status);
  }
}

Renderer::~Renderer() {
  glDisable(GL_DEPTH_TEST);

  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ibo);
  glDeleteVertexArrays(1, &_vao);

  glDeleteBuffers(1, &_fvbo);
  glDeleteVertexArrays(1, &_fvao);

  glDeleteBuffers(1, &_rtubo);

  glDeleteFramebuffers(1, &_fbo);

  glDeleteTextures(6, _fbto);
} // end of Renderer::destroy() function

ShaderManager *Renderer::getShaderManager() const {
  return _shaderManager.get();
} // end of Renderer::getShaderManager() function

void Renderer::changeRenderMode(RenderMode mode) {
  _renderMode = mode;

  if (mode == RenderMode::WIREFRAME) {
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else if (mode == RenderMode::SOLID) {
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
  } else if (mode == RenderMode::TEXTURED) {
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
} // end of Renderer::changeRenderMode() function

void Renderer::changeResolution(int width, int height) {
  camera.setResolution(width, height);

  // depth
  glBindTexture(GL_TEXTURE_2D, _fbto[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _fbto[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glGenerateMipmap(GL_TEXTURE_2D);

  for (int i = 2; i < 6; i++) {
    glActiveTexture(GL_TEXTURE0 + i - 1);
    glBindTexture(GL_TEXTURE_2D, _fbto[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  glViewport(0, 0, width, height);
}

// end of Renderer.Main.cxx
