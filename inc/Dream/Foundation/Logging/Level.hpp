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
	namespace Logging
	{	
		enum class Level : uint32
		{
			All,
			Trace,
			Info,
			Warning,
			Error,
			None,
			Progress
		};
	}

	namespace Convert
	{
		string ToString(__in Logging::Level value);
	}
}
