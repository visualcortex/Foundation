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
		enum class FileFeature : uint32
		{
			Archive			= 1,
			Compressed   	= 1 << 1,
			Directory    	= 1 << 2,
			Encrypted    	= 1 << 3,
			Hidden       	= 1 << 4,
			Normal       	= 1 << 5,
			Offline      	= 1 << 6,
			Readonly     	= 1 << 7,
			ReparsePoint 	= 1 << 8,
			SparseFile   	= 1 << 9,
			System       	= 1 << 10,
			Temporary    	= 1 << 11,
			Virtual      	= 1 << 12
		};

		DREAM_BITSET(FileFeature);
		typedef bitset<FileFeature> FileFeatures;
	}

	namespace Convert
	{
		string ToString(__in IO::FileFeatures value);
	}
}
