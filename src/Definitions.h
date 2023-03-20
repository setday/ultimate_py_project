/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Definitions.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

/* Debug memory allocation support */
# define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <new>

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#include "utils/math/MathHeaders"
#include "utils/Logger.h"

// end of Definitions.h
