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
		enum class ConsoleInputMode : uint32
		{
			ProcessedInput  = 0x0001,
			LineInput       = 0x0002,
			EchoInput       = 0x0004,
			WindowInput     = 0x0008,
			MouseInput      = 0x0010,
			InsertMode      = 0x0020,
			QuickEditMode   = 0x0040,
			ExtendedFlags   = 0x0080,
			AutoPosition    = 0x0100
		};

		DREAM_BITSET(ConsoleInputMode);
		typedef bitset<ConsoleInputMode> ConsoleInputModes;
	}

	namespace Convert
	{
		string ToString(__in System::ConsoleInputModes value);
	}
}
