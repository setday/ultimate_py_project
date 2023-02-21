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

#include "CLManager.h"
#include <fstream>
#include <iostream>

using namespace unreal_fluid::manager;

CLManager::CLManager() {
  std::cout << "Start constructing this garbadge\n";
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  for (auto platform: platforms) {
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    for (auto dev: devices) _devices.emplace_back(dev);
  }

  _context = new cl::Context(_devices.front());
  _commandQueue = new cl::CommandQueue(*_context, _devices.front());
}

CLManager::~CLManager() {
  delete _context;
  delete _commandQueue;
}

void CLManager::LoadProgram(const std::string &fileName, const std::string &programName) {
  std::ifstream file("./../src/sub_programs/" + fileName);
  std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  cl::Program program(*_context, source);

  program.build(_devices.front());
  //  if (program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(_devices.front()) != CL_BUILD_SUCCESS)
  //    std::cout << "Program with name " << programName << " was successfully failed\n";

  cl::Kernel kernel(program, programName.c_str());

  _programs[programName] = kernel;
}

void CLManager::ExecuteProgram(const std::string &programName, const std::vector<int> &bufferIDs, int numberOfRuns) {
  for (int i = 0; i < bufferIDs.size(); ++i) {
    _programs[programName].setArg(i, _buffers[bufferIDs[i]]);
  }

  _commandQueue->enqueueNDRangeKernel(_programs[programName], cl::NullRange, cl::NDRange(numberOfRuns), cl::NullRange);
}
