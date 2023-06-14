/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : CLTestScene.cxx
 * FILE AUTHORS            : Daniil Martsenyuk.
 * PURPOSE                 : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#if 0

#include <iostream>
#include "../src/core/Core.h"
#include "../src/core/components/Scene.h"

using namespace unreal_fluid;

class ClTestScene : public Scene {
  public:
  explicit ClTestScene(const compositor::Compositor *compositor) : Scene(compositor) {
    const int N = 1'000'000;
    std::vector<int> first(N, 368575);
    std::vector<int> second(N, 257808);
    std::vector<int> result(N);
    manager::CLManager *manager = &(compositor->GetCore()->clManager);

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

    first.assign(N, 368575);
    second.assign(N, 257808);
    result.assign(N, 0);

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

  ~ClTestScene() override = default;
};

#endif
