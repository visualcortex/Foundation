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

#include <Dream/Foundation/Logging/Level.hpp>

namespace Dream
{
	namespace Logging
	{
		/** Provides support for publishing log messages
		 */
		interface IPublisher : public IAbstract
		{
			/** Publishes log message
			 *	\param level Message level
			 *	\param message Message to be published
			 */
			virtual void publishLogMessage
				(__in Level level, __in const string &message) = 0;
		};
	}
}
