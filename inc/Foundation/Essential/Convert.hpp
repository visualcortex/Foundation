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

#include <Foundation/Essential/Types.hpp>

namespace Dream
{
	namespace Convert
	{
        void ToUInt8
			(__in uint32 value,
             __out uint8 *lowest,
             __out uint8 *low,
             __out uint8 *high,
             __out uint8 *highest) throw();

		int16 ToInt16
			(__in byte low,
			 __in byte high) throw();

		uint16 ToUInt16
			(__in byte low,
			 __in byte high) throw();

        void ToUInt16
			(__in uint32 value,
             __out uint16 *low,
             __out uint16 *high) throw();

		int32 ToInt32
			(__in byte lowest,
			 __in byte low,
			 __in byte high,
			 __in byte highest) throw();

		uint32 ToUInt32
			(__in byte lowest,
			 __in byte low,
			 __in byte high,
			 __in byte highest) throw();

		void ToUInt32
			(__in uint64 value, 
			 __out uint32 *low,
			 __out uint32 *high);

		uint64 ToUInt64
			(__in uint32 low,
			 __in uint32 high) throw();

		ByteArray ToByteArray
			(__in const string &value);

		string ToHexString
			(__in const byte *blob,
			 __in size_t sizeBlob);

        string ToString
            (__in const char *src,
             __in size_t sizeSource);
	}
}
