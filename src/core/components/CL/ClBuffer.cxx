/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ClBuffer.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#include "ClBuffer.h"

using namespace unreal_fluid::computing;

template<typename T>
CLBuffer<T>::CLBuffer(cl::Context const * context, cl::CommandQueue *commandQueue, cl_mem_flags flags, size_t elementCount) :
        _elementCount(elementCount), _commandQueue(commandQueue),
        _buffer(*context, flags, sizeof(T) * elementCount) {
}

template<typename T>
CLBuffer<T>::~CLBuffer() = default;

template<typename T>
void CLBuffer<T>::ReadFrom(std::vector<T> &data) {
  assert(data.size() <= _elementCount);

  _commandQueue->enqueueReadBuffer(_buffer, CL_TRUE, 0, data.size() * sizeof(T), data.data());
}

template<typename T>
void CLBuffer<T>::WriteTo(std::vector<T> &data) {
  assert(data.size() <= _elementCount);

  _commandQueue->enqueueWriteBuffer(_buffer, CL_TRUE, 0, data.size() * sizeof(T), data.data());
}

template<typename T>
cl::Buffer &CLBuffer<T>::GetBuffer() {
  return _buffer;
}

void unreal_fluid::computing::UselessFunctionCLBuffer() {
  // This function is useless, but it is used to make sure that the compiler will not optimize out the template instantiation.
  // This is needed to avoid linker errors.
  std::vector<int> data;
  auto *buffer = new unreal_fluid::computing::CLBuffer<int>(nullptr, nullptr, 0, 0);
  buffer->ReadFrom(data);
  buffer->WriteTo(data);
  delete buffer;
}
