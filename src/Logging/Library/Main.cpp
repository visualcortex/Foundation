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

#include <Dream/Foundation/Logging.hpp>

namespace Dream
{
	namespace Convert
	{
		string ToString(__in Logging::Level value)
		{
			switch (value)
			{
				case Logging::Level::All:      return "All";
				case Logging::Level::Trace:    return "Trace";
				case Logging::Level::Info:     return "Info";
				case Logging::Level::Warning:  return "Warning";
				case Logging::Level::Error:    return "Error";
				case Logging::Level::None:     return "None";
				case Logging::Level::Progress: return "Progress";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}
	}
}
