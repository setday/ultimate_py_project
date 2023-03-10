/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClManager.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include <fstream>
#include <iostream>

#include "CLManager.h"

using namespace unreal_fluid::manager;

CLManager::CLManager() {
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  for (const auto& platform: platforms) {
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    for (const auto& dev: devices) _devices.emplace_back(dev);
  }

  _context = new cl::Context(_devices.front());
  _commandQueue = new cl::CommandQueue(*_context, _devices.front());
}

CLManager::~CLManager() {
  delete _context;
  delete _commandQueue;

  for (auto *buffer: _buffers) {
    delete buffer;
  }
}

template<typename T>
unreal_fluid::computing::CLBuffer<T> * CLManager::CreateBuffer(cl_mem_flags flags, size_t elementsCount) {
  auto *buffer = new unreal_fluid::computing::CLBuffer<T>(_context, _commandQueue, flags, elementsCount);

  _buffers.emplace_back(buffer);

  return buffer;
}

void CLManager::LoadProgram(const std::string &fileName, const std::string &programName) {
  std::ifstream file("src/sub_programs/" + fileName);
  std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  cl::Program program(*_context, source);

  program.build(_devices.front());
  //  if (program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(_devices.front()) != CL_BUILD_SUCCESS)
  //    std::cout << "Program with name " << programName << " was successfully failed\n";

  cl::Kernel kernel(program, programName.c_str());

  _programs[programName] = kernel;
}

void CLManager::ExecuteProgram(const std::string &programName, const std::vector<computing::ICLBuffer *> &buffers, int numberOfRuns) {
  for (int i = 0; i < buffers.size(); ++i) {
    _programs[programName].setArg(i, _buffers[i]->GetBuffer());
  }

  _commandQueue->enqueueNDRangeKernel(_programs[programName], cl::NullRange, cl::NDRange(numberOfRuns), cl::NullRange);
}

[[maybe_unused]] void UselessFunctionClManager() {
  // This function is useless, but it is used to make sure that the compiler will not optimize out the template instantiation.
  // This is needed to avoid linker errors.
  CLManager manager;
  manager.CreateBuffer<int>(CL_MEM_READ_WRITE, 10);
}
