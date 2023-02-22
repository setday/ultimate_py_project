/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClBuffer.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <cassert>
#include <vector>

#define CL_HPP_TARGET_OPENCL_VERSION 300
#include "CL/opencl.hpp"

namespace unreal_fluid::manager {
  class CLManager;
} // unreal_fluid::manager

namespace unreal_fluid::computing {
  void UselessFunctionCLBuffer();

  class ICLBuffer {
    friend unreal_fluid::manager::CLManager;

  public:
    virtual ~ICLBuffer() = default;

  private:
    virtual cl::Buffer &GetBuffer() = 0;
  };

  template<typename T>
  class CLBuffer : public ICLBuffer {
    friend unreal_fluid::manager::CLManager;
    friend void UselessFunctionCLBuffer();

  private:
    cl::Buffer _buffer;
    cl::CommandQueue *_commandQueue;
    size_t _elementCount;

  private:
    CLBuffer(cl::Context *context, cl::CommandQueue *commandQueue, cl_mem_flags flags, size_t elementCount);

  public:
    ~CLBuffer() override;

    void ReadFrom(std::vector<T> &data);
    void WriteTo(std::vector<T> &data);

  private:
    cl::Buffer &GetBuffer() override;
  };
} // unreal_fluid::cl

// end of ClBuffer.h
