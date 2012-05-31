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

#include <Dream/Foundation/Logging/Formatter.hpp>

namespace Dream
{
	namespace Logging
	{
		class XmlFormatter : public IFormatter
		{
			public:
				virtual string formatLogRecord(__in const Record &record);
		};
	}
}
