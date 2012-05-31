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

#include <Dream/Foundation/Logging/Publisher.hpp>
#include <Dream/Foundation/System.hpp>

namespace Dream
{
	namespace Logging
	{
		/** Provides support for publishing log messages to console
		 */
		class ConsolePublisher : public IPublisher
		{
			public:
				ConsolePublisher();

			public:
				virtual void publishLogMessage
					(__in Level level,
					 __in const string &message);

			private:
				System::Console::CaretPosition m_positionCaret;
				System::Console::ScreenResolution m_resolutionScreen;
		};
	}
}
