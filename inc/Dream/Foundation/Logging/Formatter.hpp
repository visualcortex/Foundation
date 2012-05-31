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

#include <Dream/Foundation/Logging/Record.hpp>

namespace Dream
{
	namespace Logging
	{
		/** Provides support for formatting log records
		 */
		interface IFormatter : public IAbstract
		{
			virtual string formatLogRecord(__in const Record &record) = 0;
		};
	}
}
