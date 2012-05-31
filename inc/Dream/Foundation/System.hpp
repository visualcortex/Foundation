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

#include <Dream/Foundation/System/Console.hpp>
#include <Dream/Foundation/System/ConsoleInputMode.hpp>
#include <Dream/Foundation/System/ConsoleOutputMode.hpp>
#include <Dream/Foundation/System/Environment.hpp>
#include <Dream/Foundation/System/Exception.hpp>

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	pragma comment(lib, DREAM_COMPOSE_LIBRARY_NAME("Dream.Foundation.System"))
#endif
