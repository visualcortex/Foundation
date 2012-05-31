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

#include <Dream/Foundation/Essential/Types.hpp>

namespace Dream
{
	namespace IO
	{
		enum class FileAccessRights : uint32
		{
			Read, 
			Write, 
			ReadWrite
		};
	}

	namespace Convert
	{
		string ToString(__in IO::FileAccessRights value);
	}
}