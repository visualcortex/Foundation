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

#include "Precompiled.hpp"

#include <Dream/Foundation/System.hpp>

namespace Dream
{
	namespace Convert
	{
		string ToString(__in System::ConsoleInputModes value)
		{
			std::ostringstream stream;

			if (value & System::ConsoleInputMode::ProcessedInput)	stream << "ProcessedInput|";
			if (value & System::ConsoleInputMode::LineInput)		stream << "LineInput|";
			if (value & System::ConsoleInputMode::EchoInput)		stream << "EchoInput|";
			if (value & System::ConsoleInputMode::WindowInput)		stream << "WindowInput|";
			if (value & System::ConsoleInputMode::MouseInput)		stream << "MouseInput|";
			if (value & System::ConsoleInputMode::InsertMode)		stream << "InsertMode|";
			if (value & System::ConsoleInputMode::QuickEditMode)	stream << "QuickEditMode|";
			if (value & System::ConsoleInputMode::ExtendedFlags)	stream << "ExtendedFlags|";
			if (value & System::ConsoleInputMode::AutoPosition)		stream << "AutoPosition|";

			return stream.str();
		}

		string ToString(__in System::ConsoleOutputModes value)
		{
			std::ostringstream stream;

			if (value & System::ConsoleOutputMode::ProcessedOutput)	stream << "ProcessedOutput|";
			if (value & System::ConsoleOutputMode::WrapAtEOLOutput)	stream << "WrapAtEOLOutput|";

			return stream.str();
		}
	}
}
