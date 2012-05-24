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

#include <Foundation/Essential/Abstract.hpp>
#include <Foundation/Essential/Action.hpp>
#include <Foundation/Essential/Algorithm.hpp>
#include <Foundation/Essential/Assert.hpp>
#include <Foundation/Essential/Convert.hpp>
#include <Foundation/Essential/Exception.hpp>
#include <Foundation/Essential/Noncopyable.hpp>
#include <Foundation/Essential/Nullable.hpp>
#include <Foundation/Essential/Platform.hpp>
#include <Foundation/Essential/Results.hpp>
#include <Foundation/Essential/Stream.hpp>
#include <Foundation/Essential/Time.hpp>
#include <Foundation/Essential/Types.hpp>

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	pragma comment(lib, DREAM_COMPOSE_LIBRARY_NAME("Dream.Foundation.Essential"))
#endif
