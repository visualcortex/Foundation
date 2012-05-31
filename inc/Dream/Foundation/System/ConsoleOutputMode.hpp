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

#include <Dream/Foundation/Essential.hpp>

namespace Dream
{
	namespace System
	{
		enum class ConsoleOutputMode : uint32
		{
			ProcessedOutput	= 0x0001,
			WrapAtEOLOutput = 0x0002
		};

		DREAM_BITSET(ConsoleOutputMode);
		typedef bitset<ConsoleOutputMode> ConsoleOutputModes;
	}

	namespace Convert
	{
		string ToString(__in System::ConsoleOutputModes value);
	}
}
