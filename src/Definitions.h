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
#ifndef NDEBUG
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy
{
public:
  __Dummy( void )
  {
    SetDbgMemHooks();
  }
} __ooppss;

#endif /* _DEBUG */

#ifdef _DEBUG
# ifdef _CRTDBG_MAP_ALLOC
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
# endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

#include "utils/math/MathHeaders"
#include "utils/Logger.h"

// end of Definitions.h
