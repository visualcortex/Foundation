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

#include <Dream/Foundation/Logging/ConsolePublisher.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.ConsolePublisher"

namespace Dream
{
	namespace Logging
	{
		ConsolePublisher::ConsolePublisher()
		{
			m_positionCaret = System::Console::GetCaretPosition();
			m_resolutionScreen = System::Console::GetScreenResolution();

	#if 0
			std::wcout.imbue(std::locale("Russian_Russia.866"));
	#endif

			System::Console::SetConsoleInputMode
				(System::ConsoleInputMode::InsertMode|
				 System::ConsoleInputMode::QuickEditMode|
				 System::ConsoleInputMode::ExtendedFlags|
				 System::ConsoleInputMode::InsertMode);

			System::Console::SetConsoleOutputMode
				(System::ConsoleOutputMode::WrapAtEOLOutput|
				 System::ConsoleOutputMode::ProcessedOutput);
		}

		// TODO: Level coloring...
		void ConsolePublisher::publishLogMessage
			(__in Level level, __in const string &message)
		{
			std::cout.clear();

			int cx = std::get<0>(m_resolutionScreen);

			switch (level)
			{
				case Level::Progress:
					{
						System::Console::SetCaretPosition(m_positionCaret);
						std::cout << message.substr(0, cx - 1);
						std::cout << string(cx - 1 - std::min<size_t>(cx - 1, message.size()), ' ');
					}
					break;

				default:
					{
						System::Console::SetCaretPosition(m_positionCaret);
						std::cout << string(cx - 1, ' ');
						System::Console::SetCaretPosition(m_positionCaret);
						std::cout << message << std::endl;
						m_positionCaret = System::Console::GetCaretPosition();
					}
					break;
			}

			std::cout.clear();
		}
	}
}
