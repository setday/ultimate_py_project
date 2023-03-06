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
 * authors of this pressureSolving.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#ifdef _DEBUG
#define LOG_FATAL(message) Logger::log(Logger::Level::FATAL, message, __FILE__, __LINE__)
#define LOG_ERROR(message) Logger::log(Logger::Level::ERR, message, __FILE__, __LINE__)
#define LOG_WARNING(message) Logger::log(Logger::Level::WARNING, message)
#define LOG_INFO(message) Logger::log(Logger::Level::INFO, message)
#define LOG_DEBUG(message) Logger::log(Logger::Level::DEBUG, message)
#else
#define LOG_FATAL(message) Logger::log(Logger::Level::FATAL, message, __FILE__, __LINE__)
#define LOG_ERROR(message) Logger::log(Logger::Level::ERR, message, __FILE__, __LINE__)
#define LOG_WARNING(message) {}
#define LOG_INFO(message) Logger::log(Logger::Level::INFO, message)
#define LOG_DEBUG(message) {}
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

  /// Logs a message to the console or file depending on the level and mode.
  /// @param level The level of the message.
  /// @param message The message to log.
  /// @param file The file where the message was logged. (optional)
  /// @param line The line where the message was logged. (optional)
  template<typename T>
  static void log(Level level, const T &message, std::string_view file = "", int line = -1) {
    switch (level) {
      case Level::DEBUG:
        std::cout << "|===| [DEBUG] " << message << std::endl;
        break;
      case Level::INFO:
        std::cout << "> [INFO] " << message;
        break;
      case Level::WARNING:
        std::cout << "> [WARNING] " << message;
        break;
      case Level::ERR:
        std::cout << ">>> [ERROR] " << message;
        break;
      case Level::FATAL:
        std::cout << ">>> [FATAL] " << message;
        break;
    }

    if (file != "" && line != -1) {
      std::cout << " (in file " << file << " at line " << line << ")";
    } else if (file != "") {
      std::cout << " (in file " << file << ")";
    } else if (line != -1) {
      std::cout << " (at line " << line << ")";
    }

    std::cout << std::endl;

    if (level == Level::FATAL) {
      exit(1);
    }
  }
};

// end of Logger.h
