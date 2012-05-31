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

#include <Dream/Foundation/Logging/ConsolePublisher.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>
#include <Dream/Foundation/Logging/FilePublisher.hpp>
#include <Dream/Foundation/Logging/Filter.hpp>
#include <Dream/Foundation/Logging/Formatter.hpp>
#include <Dream/Foundation/Logging/FunctionMarker.hpp>
#include <Dream/Foundation/Logging/Handler.hpp>
#include <Dream/Foundation/Logging/Journal.hpp>
#include <Dream/Foundation/Logging/Level.hpp>
#include <Dream/Foundation/Logging/Manager.hpp>
#include <Dream/Foundation/Logging/Publisher.hpp>
#include <Dream/Foundation/Logging/Record.hpp>
#include <Dream/Foundation/Logging/TextFormatter.hpp>
#include <Dream/Foundation/Logging/XmlFormatter.hpp>

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	pragma comment(lib, DREAM_COMPOSE_LIBRARY_NAME("Dream.Foundation.Logging"))
#endif
