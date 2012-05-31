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

#include <Dream/Foundation/Essential/Platform.hpp>

namespace Dream
{
#if DREAM_COMPILER_NAME == DREAM_COMPILER_MSVC

	typedef __int8 int8;
	typedef unsigned __int8 uint8;

	typedef __int16 int16;
	typedef unsigned __int16 uint16;

	typedef __int32 int32;
	typedef unsigned __int32 uint32;

	typedef __int64 int64;
	typedef unsigned __int64 uint64;

#endif

	typedef uint8 byte;
	typedef uint16 word;
	typedef uint32 dword;
	typedef uint64 qword;

	typedef unsigned char uchar;
	typedef unsigned int uint;
	typedef unsigned long int ulong;
	typedef unsigned short int ushort;
}
