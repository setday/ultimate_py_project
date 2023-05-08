/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClTestScene.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include <iostream>
#include "../src/core/Core.h"
#include "../src/core/components/scene/Scene.h"

#define CL_HPP_TARGET_OPENCL_VERSION 300

#include "CL/opencl.hpp"

using namespace unreal_fluid;
using namespace std;

#include "chrono"

long long currentTimeMicros();


class ClTestScene : public IScene {
  public:
    explicit ClTestScene(compositor::SceneCompositor const * compositor) : IScene() {
      // Initialize OpenCL platform, device, and context
      std::vector<cl::Platform> platforms;
      cl::Platform::get(&platforms);
      auto platform = platforms[0];
      std::vector<cl::Device> devices;
      platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
      auto device = devices[0];
      auto context = cl::Context(device);

      // Create a program object with the kernel source code
      std::string kernelSource = "__kernel void add(__global const int* a, __global const int* b, __global int* c) {"
              "    const int i = get_global_id(0);"
              "    c[i] = a[i] + b[i];"
              "}";
      auto program = cl::Program(context, kernelSource);

      // Build the program for the device
      program.build("-cl-std=CL1.2");

      // Create the input and output buffers on the device
      const int N = 1024;
      auto aBuffer = cl::Buffer(context, CL_MEM_READ_ONLY, N * sizeof(int));
      auto bBuffer = cl::Buffer(context, CL_MEM_READ_ONLY, N * sizeof(int));
      auto cBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, N * sizeof(int));

      // Write the input data from the host to the input buffers on the device
      std::vector<int> a(N), b(N);
      for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = N - i;
      }
      cl::CommandQueue queue(context, device);
      queue.enqueueWriteBuffer(aBuffer, CL_TRUE, 0, N * sizeof(int), a.data());
      queue.enqueueWriteBuffer(bBuffer, CL_TRUE, 0, N * sizeof(int), b.data());

      // Set the arguments for the kernel function
      auto kernel = cl::Kernel(program, "add");
      kernel.setArg(0, aBuffer);
      kernel.setArg(1, bBuffer);
      kernel.setArg(2, cBuffer);

      // Enqueue the kernel function to the command queue
      const size_t globalWorkSize = N;
      const size_t localWorkSize = 64; // Use 64 work-items per work-group
      const size_t numWorkGroups = globalWorkSize / localWorkSize;
      queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(globalWorkSize), cl::NDRange(localWorkSize));

      // Read the output data from the output buffer on the device to the host
      std::vector<int> c(N);
      queue.enqueueReadBuffer(cBuffer, CL_TRUE, 0, N * sizeof(int), c.data());

      // Print the result

      bool ok = true;
      for (int i = 0; i < N; i++) {
        if (c[i] != N){
          ok = false;
          break;
        }
      }
      if (ok){
        Logger::logInfo("CL works properly");
      }else{
        Logger::logFatal("CL does not work properly");
      }
    }

    void update() override {}

    void render() override {}

    ~ClTestScene() override = default;
};
