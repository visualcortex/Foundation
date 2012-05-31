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
		enum class FileShareMode : uint32
		{
			None,
			Read,
			Write,
			ReadWrite,
			Delete
		};
	}

	namespace Convert
	{
		string ToString(__in IO::FileShareMode value);
	}
}
