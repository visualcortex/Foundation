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

#include <Dream/Foundation/Essential/Abstract.hpp>
#include <Dream/Foundation/Essential/Action.hpp>
#include <Dream/Foundation/Essential/Algorithm.hpp>
#include <Dream/Foundation/Essential/Assert.hpp>
#include <Dream/Foundation/Essential/Bitset.hpp>
#include <Dream/Foundation/Essential/Convert.hpp>
#include <Dream/Foundation/Essential/Exception.hpp>
#include <Dream/Foundation/Essential/Noncopyable.hpp>
#include <Dream/Foundation/Essential/Nullable.hpp>
#include <Dream/Foundation/Essential/Platform.hpp>
#include <Dream/Foundation/Essential/Results.hpp>
#include <Dream/Foundation/Essential/Stream.hpp>
#include <Dream/Foundation/Essential/Time.hpp>
#include <Dream/Foundation/Essential/Types.hpp>
#include <Dream/Foundation/Essential/TypeTraits.hpp>

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	pragma comment(lib, DREAM_COMPOSE_LIBRARY_NAME("Dream.Foundation.Essential"))
#endif
