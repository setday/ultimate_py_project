/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClManager.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "./../../../components/CL/ClBuffer.h"

namespace unreal_fluid::manager {

  class CLManager {
    std::vector<cl::Device> _devices;
    std::vector<computing::ICLBuffer *> _buffers;
    cl::Context *_context;
    cl::CommandQueue *_commandQueue;
    std::unordered_map<std::string, cl::Kernel> _programs;

  public:
    CLManager();
    ~CLManager();

    template<typename T>
    computing::CLBuffer<T> * CreateBuffer(cl_mem_flags flags, size_t elementsCount);

    void LoadProgram(const std::string &fileName, const std::string &programName);
    void ExecuteProgram(const std::string &programName, const std::vector<computing::ICLBuffer *> &buffers, int numberOfRuns);
  };
} // namespace unreal_fluid

// end of ClManager.h
