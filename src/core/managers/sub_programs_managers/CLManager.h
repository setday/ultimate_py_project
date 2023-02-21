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

#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>

namespace unreal_fluid::manager {

  class CLManager {
    std::vector<cl::Device> _devices;
    std::vector<cl::Buffer> _buffers;
    cl::Context *_context;
    cl::CommandQueue *_commandQueue;
    std::unordered_map<std::string, cl::Kernel> _programs;

  public:
    CLManager();
    ~CLManager();

    template<typename T>
    int CreateBuffer(cl_mem_flags flags, size_t size) {
      _buffers.emplace_back(*_context, flags, size * sizeof(T));
      return _buffers.size() - 1;
    }

    template<typename T>
    void ReadBuffer(int id, std::vector<T> &data) {
      _commandQueue->enqueueReadBuffer(_buffers[id], CL_TRUE, 0, data.size() * sizeof(T), data.data());
    }

    template<typename T>
    void WriteBuffer(int id, std::vector<T> &data) {
      _commandQueue->enqueueWriteBuffer(_buffers[id], CL_TRUE, 0, data.size() * sizeof(T), data.data());
    }

    void LoadProgram(const std::string &fileName, const std::string &programName);
    void ExecuteProgram(const std::string &programName, const std::vector<int> &bufferIDs, int numberOfRuns);
  };
} // namespace unreal_fluid

// end of ClManager.h
