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
using namespace std::chrono;

class CLTestScene : Scene {
public:
  CLTestScene() {
    const int N = 10000000;
    std::vector<int> first(N, 368575), second(N, 257808), result(N);
    manager::CLManager manager;

    manager.LoadProgram("CLTest.clkc", "add");

    int idA = manager.CreateBuffer<int>(CL_MEM_READ_ONLY, N);
    int idB = manager.CreateBuffer<int>(CL_MEM_READ_ONLY, N);
    int idC = manager.CreateBuffer<int>(CL_MEM_WRITE_ONLY, N);

    manager.WriteBuffer(idA, first);
    manager.WriteBuffer(idB, second);
    auto start = high_resolution_clock::now();
    manager.ExecuteProgram("add", {idA, idB, idC}, N);
    manager.ReadBuffer(idC, result);
    std::cout << duration_cast<microseconds>(high_resolution_clock::now() - start).count() << "\n"; // 23870

    first.assign(N, 368575), second.assign(N, 257808), result.assign(N, 0);
    start = high_resolution_clock::now();
      for (int k = 0; k < N; ++k) {
        result[k] = first[k] + second[k];
      }
    std::cout << duration_cast<microseconds>(high_resolution_clock::now() - start).count(); // 49276
  }
};
