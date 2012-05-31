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
	namespace IO 
	{
		/** Specifies how a file should be opened
	     */
		enum class FileOpenMode : uint32
		{
			Create, 
			CreateNew,
			Open,
			OpenExisting,
			Append,
			Truncate
		};
	}

	namespace Convert
	{
		string ToString(__in IO::FileOpenMode value);
	}
}
