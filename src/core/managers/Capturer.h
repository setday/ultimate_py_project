//
// Created by Vasya on 21.03.2023.
//
/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher
 *    school of economics in Saint-Petersburs).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Capturer.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */
#include "../../render/Renderer.h"
#include <GL/gl.h>
#include <GL/glaux.h>
#pragma once


namespace unreal_fluid::recorder{
  enum class PixelFormats{
    RGB
  };

//  struct Frame{
//    char* pixelArray;
//    unsigned width;
//    unsigned height;
//    unsigned pixelFormat;
//  };
  typedef struct Frame {
    GLint sizeX, sizeY;
    unsigned char *data;
  };

  class Capturer {
    //unreal_fluid::render::Renderer *_renderer;
    Capturer();
    ~Capturer();
    Frame nextFrame();
  };
}



// end of Capturer.h