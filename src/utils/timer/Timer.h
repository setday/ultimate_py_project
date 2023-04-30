/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : Timer.h
 * AUTHOR OF THIS FILE     : Serkov Alexander
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <chrono>
#include <cmath>

namespace unreal_fluid::utils {
  class Timer {
  public:
    enum class TimeType {
      SECONDS,
      MILLISECONDS,
      MICROSECONDS,
      NANOSECONDS
    };

    enum class State {
      RUNNING,
      PAUSED
    };
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _localStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> _localEnd;
    std::chrono::time_point<std::chrono::high_resolution_clock>::duration _accumulatedTime;
    State _localState = State::RUNNING;

    unsigned int _counter = 0;

  public:
    Timer();

    /// Get current time.
    /// @return current time as std::chrono::time_point<std::chrono::high_resolution_clock>.
    static std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime();
    /// Get current time.
    /// @return current time as double.
    template<TimeType timeType = TimeType::SECONDS>
    static double getCurrentTimeAsDouble() {
      return convertTime<TimeType::NANOSECONDS, timeType>(getCurrentTime().time_since_epoch().count());
    }

    template<TimeType timeTypeFrom = TimeType::NANOSECONDS, TimeType timeTypeTo = TimeType::SECONDS>
    static double convertTime(double time) {
      double delta = 0;

      switch (timeTypeFrom) {
        case TimeType::SECONDS:
          delta = time;
          break;
        case TimeType::MILLISECONDS:
          delta = time / 1000;
          break;
        case TimeType::MICROSECONDS:
          delta = time / 1000000;
          break;
        case TimeType::NANOSECONDS:
          delta = time / 1000000000;
          break;
      }

      switch (timeTypeTo) {
        case TimeType::SECONDS:
          return delta;
        case TimeType::MILLISECONDS:
          return delta * 1000;
        case TimeType::MICROSECONDS:
          return delta * 1000000;
        case TimeType::NANOSECONDS:
          return delta * 1000000000;
      }
    }

    /// @brief Pause timer.
    /// @details If timer is already paused, nothing happens. If timer is running, it will be paused.
    void pause();
    /// @brief Resume timer.
    /// @details If timer is already running, nothing happens. If timer is paused, it will be resumed.
    void resume();

    void reset();

    /// @brief Get elapsed time.
    /// @details If timer is running, it will return time from start to now.
    template<TimeType timeType = TimeType::SECONDS>
    [[nodiscard]] double getElapsedTime() const {
      std::chrono::duration delta =
              std::chrono::duration_cast<std::chrono::nanoseconds>(_accumulatedTime + (_localEnd - _localStart));

      if (_localState == State::RUNNING) {
        delta = _accumulatedTime + (getCurrentTime() - _localStart);
      }

      return convertTime<TimeType::NANOSECONDS, timeType>(delta.count());
    }
    /// @brief Get elapsed time and reset timer.
    /// @details If timer is running, it will return time from start to now and reset timer.
    template<TimeType timeType = TimeType::SECONDS>
    double getElapsedTimeAndReset() {
      double result = getElapsedTime<timeType>();

      reset();

      return result;
    }

    /// @brief Increment counter.
    /// @details Counter is used to calculate average time.
    void incrementCounter();
    /// @brief Get counter.
    /// @details Counter is used to calculate average time.
    [[nodiscard]] unsigned int getCounter() const {
      return _counter;
    }

    /// @brief Get average time.
    /// @details If timer is running, it will return average time from start to now.
    template<TimeType timeType = TimeType::SECONDS>
    [[nodiscard]] double getAverageTime() const {
      return getElapsedTime<timeType>() / _counter;
    }
  };
}

// end of Timer.h
