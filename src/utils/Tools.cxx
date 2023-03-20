/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : ultimate_py_project
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : Tools.cxx
* PURPOSE   : time measurement
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#include "Tools.h"

long long getMicroseconds() {
    typedef std::chrono::microseconds mcr;
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::duration<float> fsec;
    auto tp = Time::now();
    mcr t_mc = std::chrono::duration_cast<mcr>(tp.time_since_epoch());
    return t_mc.count();
}
