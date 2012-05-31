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
		/** Provides the fields that represent reference points in streams for seeking
		 */
		enum class FileSeekMode : uint32
		{
			Begin,
			Current,
			End
		};
	}

	namespace Convert
	{
		string ToString(__in IO::FileSeekMode value);
	}
}
