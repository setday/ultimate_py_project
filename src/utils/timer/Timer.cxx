/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : Timer.cxx
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "Timer.h"

using namespace unreal_fluid::utils;

Timer::Timer() {
  reset();
}

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::getCurrentTime() {
  return std::chrono::high_resolution_clock::now();
}

void Timer::pause() {
  _localEnd = getCurrentTime();

  _accumulatedTime += _localEnd - _localStart;

  _localStart = _localEnd;

  _localState = State::PAUSED;
}

void Timer::resume() {
  _localState = State::RUNNING;

  _localStart = _localEnd = getCurrentTime();
}

void Timer::reset() {
  _accumulatedTime = std::chrono::time_point<std::chrono::high_resolution_clock>::duration::zero();

  _counter = 0;

  _localStart = _localEnd = getCurrentTime();
}

void Timer::incrementCounter() {
  _counter++;
}

// end of Timer.cxx
