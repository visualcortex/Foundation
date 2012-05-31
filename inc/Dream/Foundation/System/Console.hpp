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

#include <Dream/Foundation/System/ConsoleInputMode.hpp>
#include <Dream/Foundation/System/ConsoleOutputMode.hpp>

namespace Dream
{
	namespace System
	{
		class Console
		{
			public:
				typedef std::tuple<int, int> CaretPosition;
				typedef std::tuple<int, int> ScreenResolution;

			public:
				/// Sets the cursor position
				static void SetCaretPosition
					(__in const CaretPosition &value);

				/// Retrieves the caret position
				static CaretPosition GetCaretPosition();

				/// Retrieves the screen resolution
				static ScreenResolution GetScreenResolution();

	            /// Sets the console input mode
	            static void SetConsoleInputMode
	            	(__in ConsoleInputModes value);

	            /// Sets the console output mode
	            static void SetConsoleOutputMode
	            	(__in ConsoleOutputModes value);
		};
	}
}
