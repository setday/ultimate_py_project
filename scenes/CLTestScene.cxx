/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CLTestScene.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include <iostream>
#include "../src/core/Core.h"

using namespace unreal_fluid;

class CLTestScene : Scene {
public:
  CLTestScene(compositor::Compositor *compositor) : Scene(compositor) {
    const int N = 100000000;
    std::vector<int> first(N, 368575), second(N, 257808), result(N);
    manager::CLManager *manager = &(compositor->core->clManager);

    manager->LoadProgram("CLTest.clkc", "add");

    auto idA = manager->CreateBuffer<int>(CL_MEM_READ_ONLY, N);
    auto idB = manager->CreateBuffer<int>(CL_MEM_READ_ONLY, N);
    auto idC = manager->CreateBuffer<int>(CL_MEM_WRITE_ONLY, N);

    auto start = std::chrono::high_resolution_clock::now();
    {
      idA->ReadFrom(first);
      idB->ReadFrom(second);
      manager->ExecuteProgram("add", {idA, idB, idC}, N);
      idC->WriteTo(result);
    }
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start
            ).count() << "\n"; // 3984

    first.assign(N, 368575), second.assign(N, 257808), result.assign(N, 0);

    start = std::chrono::high_resolution_clock::now();
    {
      for (int k = 0; k < N; ++k) {
        result[k] = first[k] + second[k];
      }
    }
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start
            ).count(); // 5951
  }
};
