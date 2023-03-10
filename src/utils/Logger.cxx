/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Logger.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#include "Logger.h"

void LoggerExample() {
  LOG_FATAL("Hello, world!");
  LOG_ERROR("Hello, world!");
  LOG_WARNING("Hello, world!");
  LOG_INFO("Hello, world!");
  LOG_DEBUG("Hello, world!");
}

// end of Logger.cxx
