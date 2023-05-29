/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Parser.h
 * PURPOSE   : parse logic is now less messy
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../physics/IPhysicalObject.h"
#include "../render/components/RenderObject.h"

namespace unreal_fluid::physics {

  class Parser {
  public:
    static void parsePlane(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects);
    static void parseSphere(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects);
    static void parseMesh(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects);
    static void parseContainer(IPhysicalObject &object, std::vector<render::RenderObject *> &renderObjects);
  };

} // namespace unreal_fluid::physics

// end of CollisionSolver.h
