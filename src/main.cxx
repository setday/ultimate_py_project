/* Note: No copyright in this file because it is not a part of the project. */

#include "core/Core.h"

int main() {
  unreal_fluid::Core core;
  core.run();
}

// end of main.cxx

long long currentTimeMicros() {
  typedef std::chrono::microseconds mcr;
  typedef std::chrono::high_resolution_clock Time;
  typedef std::chrono::duration<float> fsec;
  auto tp = Time::now();
  mcr t_mc = std::chrono::duration_cast<mcr>(tp.time_since_epoch());
  return t_mc.count();
}