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
  CLTestScene() {
    std::vector<int> first(10, 1), second(10, 387971), result(10);
    manager::CLManager manager;

    manager.LoadProgram("CLTest.clkc", "add");

    int idA = manager.CreateBuffer<int>(CL_MEM_READ_ONLY, 10);
    int idB = manager.CreateBuffer<int>(CL_MEM_READ_ONLY, 10);
    int idC = manager.CreateBuffer<int>(CL_MEM_WRITE_ONLY, 10);

    manager.WriteBuffer(idA, first);
    manager.WriteBuffer(idB, second);

    manager.ExecuteProgram("add", {idA, idB, idC}, 10);

    manager.ReadBuffer(idC, result);
    for (auto el: result) std::cout << el << " ";
    std::cout << "\n";
  }
};
