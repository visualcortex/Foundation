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
		enum class FileMapAccessRights : uint32
		{
			Read,
			ReadWrite,
			ExecuteRead,
			ExecuteReadWrite
		};
	}

	namespace Convert
	{
		string ToString(__in IO::FileMapAccessRights value);
	}
}
