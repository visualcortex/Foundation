/******************************************************************************
 * @file
 * @author Ivan Makarov <im.visualcortex@gmail.com>
 * 
 * @section LICENSE
 *
 * Copyright (C) 2012, Ivan Makarov
 * Licensed under the MIT license.
 *
 *****************************************************************************/

#pragma once

//-----------------------------------------------------------------------------
// STD
//-----------------------------------------------------------------------------

#include <io.h>
#include <sstream>

//-----------------------------------------------------------------------------
// FOUNDATION
//-----------------------------------------------------------------------------

#include <Dream/Foundation/Essential.hpp>
#include <Dream/Foundation/System.hpp>

//-----------------------------------------------------------------------------
// PLATFORM
//-----------------------------------------------------------------------------

#if DREAM_PLATFORM_OS_NAME == DREAM_PLATFORM_OS_WINDOWS
#	include <windows.h>
#else
#	error "Only Microsoft Windows supported."
#endif
