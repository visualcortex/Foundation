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

#include "../Precompiled.hpp"

#include <Dream/Foundation/System/Console.hpp>
#include <Dream/Foundation/System/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.System.Console"

namespace Dream 
{
	namespace System 
	{
		void Console::SetCaretPosition(__in const Console::CaretPosition &value)
		{
			HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			if (hStdOutput != INVALID_HANDLE_VALUE)
			{
				COORD pos;
			
				pos.X = static_cast<SHORT>(std::get<0>(value));
				pos.Y = static_cast<SHORT>(std::get<1>(value));

				if (SetConsoleCursorPosition(hStdOutput, pos) != 0)
					return;
			}

			throw Exception(SOURCE_CLASS);
		}

		Console::CaretPosition Console::GetCaretPosition()
		{
			HANDLE hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
			if (hStdOutput != INVALID_HANDLE_VALUE)
			{
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				if (::GetConsoleScreenBufferInfo(hStdOutput, &csbi) != 0)
					return CaretPosition(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
			}

			throw Exception(SOURCE_CLASS);
		}

		Console::ScreenResolution Console::GetScreenResolution()
		{
			HANDLE hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
			if (hStdOutput != INVALID_HANDLE_VALUE)
			{
				CONSOLE_SCREEN_BUFFER_INFO scbi;
				if (::GetConsoleScreenBufferInfo(hStdOutput, &scbi) != 0)
					return ScreenResolution(scbi.dwSize.X, scbi.dwSize.Y);
			}

			throw Exception(SOURCE_CLASS);
		}

		void Console::SetConsoleInputMode(__in ConsoleInputModes value)
		{
			HANDLE hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
			if (hStdInput != INVALID_HANDLE_VALUE)
			{
				if (::SetConsoleMode(hStdInput, value.flags) != 0)
					return;
			}

			throw Exception(SOURCE_CLASS);
		}

		void Console::SetConsoleOutputMode(__in ConsoleOutputModes value)
		{
			HANDLE hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
			if (hStdOutput != INVALID_HANDLE_VALUE)
			{
				if (::SetConsoleMode(hStdOutput, value.flags) != 0)
					return;
			}

			throw Exception(SOURCE_CLASS);
		}
	}
 }
