/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Logger.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#define _DEBUG

#ifdef _DEBUG
#define LOG_DEBUG(...) Logger::log(Logger::Level::DEBUG, __VA_ARGS__)
#define LOG_INFO(...) Logger::log(Logger::Level::INFO, __VA_ARGS__)
#define LOG_WARNING(...) Logger::log(Logger::Level::WARNING, __VA_ARGS__)
#define LOG_ERROR(...) { Logger::log(Logger::Level::ERR, __VA_ARGS__); \
                         Logger::logPlace(__FILE__, __LINE__); }
#define LOG_FATAL(...) { Logger::logPlace(__FILE__, __LINE__); \
                         Logger::log(Logger::Level::FATAL, __VA_ARGS__); }
#else
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARNING(...)
#define LOG_ERROR(...) { Logger::log(Logger::Level::ERR, __VA_ARGS__); \
                         Logger::logPlace(__FILE__, __LINE__); }
#define LOG_FATAL(...) { Logger::logPlace(__FILE__, __LINE__); \
                         Logger::log(Logger::Level::FATAL, __VA_ARGS__); }
#endif

class Logger {
public:
  enum class Level {
    DEBUG,
    INFO,
    WARNING,
    ERR, // ERROR is already defined in Windows.h
    FATAL
  };

private:
  template<typename Arg>
  static void logObject(const Arg &object) {
    std::cout << object;
  }

public:
  /// Log a lots of objects.
  /// @param level The level of the message.
  /// @param objects The objects to log.
  /// @attention to use this method you should overload std::to_string for your class
  template<typename... Args>
  static void log(Level level, const Args &... objects) {
    switch (level) {
      case Level::DEBUG:
        logObject("|===| [DEBUG] ");
        break;
      case Level::INFO:
        logObject("> [INFO] ");
        break;
      case Level::WARNING:
        logObject("> [WARNING] ");
        break;
      case Level::ERR:
        logObject(">>> [ERROR] ");
        break;
      case Level::FATAL:
        logObject(">>> [FATAL] ");
        break;
    }

    ((logObject(objects), logObject(' ')), ...);

#if 0
    if (file != "" && line != -1) {
      logObjects(" (in file ", file, " at line ", line, ")");
    } else if (file != "") {
      logObjects(" (in file ", file, ")");
    } else if (line != -1) {
      logObjects(" (at line ", line, ")");
    }
#endif

    logObject('\n');

    if (level == Level::FATAL) {
      exit(1);
    }
  }

  /// Log place of call
  /// @param file file name
  /// @param line line number
  static void logPlace(std::string_view file = "", int line = -1) {
    if (file != "" && line != -1) {
      logObject(" (in file ");
      logObject(file);
      logObject(" at line ");
      logObject(line);
      logObject(")");
    } else if (file != "") {
      logObject(" (in file ");
      logObject(file);
      logObject(")");
    } else if (line != -1) {
      logObject(" (at line ");
      logObject(line);
      logObject(")");
    }
  }

  /// Log a lots of objects with info level
  /// @attention to use this method you should overload std::to_string for your class
  /// @param objects objects to log
  template<typename... Args>
  static void logInfo(const Args &... objects) {
    log(Level::INFO, objects...);
  }

  /// Log a lots of objects with debug level
  /// @attention to use this method you should overload std::to_string for your class
  /// @param objects objects to log
  template<typename... Args>
  static void logDebug(const Args &... objects) {
    log(Level::DEBUG, objects...);
  }

  /// Log a lots of objects with warning level
  /// @attention to use this method you should overload std::to_string for your class
  /// @param objects objects to log
  template<typename... Args>
  static void logWarning(const Args &... objects) {
    log(Level::WARNING, objects...);
  }

  /// Log a lots of objects with error level
  /// @attention to use this method you should overload std::to_string for your class
  /// @param objects objects to log
  template<typename... Args>
  static void logError(const Args &... objects) {
    log(Level::ERR, objects...);
  }

  /// Log a lots of objects with fatal level
  /// @attention to use this method you should overload std::to_string for your class
  /// @param objects objects to log
  template<typename... Args>
  static void logFatal(const Args &... objects) {
    log(Level::FATAL, objects...);
  }
};

// end of Logger.h
