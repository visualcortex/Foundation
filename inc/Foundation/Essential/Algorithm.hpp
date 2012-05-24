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

#include <Foundation/Essential/Convert.hpp>

#include <algorithm>

namespace Dream
{
	namespace Algorithm
	{
		template<class T>
			bool inrange(__in T value, __in T valueMin, __in T valueMax)
			{
				return valueMin <= value && value <= valueMax;
			}

		/// Performs a circular left shift operation
		inline uint32 CircularShift(__in int32 numBitsToShift, __in int32 value)
		{
			return ((value << numBitsToShift) & 0xFFFFFFFF) 
					| ((value & 0xFFFFFFFF) >> (32 - numBitsToShift));
		}

        inline uint32 ReverseBytes(__in uint32 value)
        {
            uint8 lowest, low, high, highest;
            Convert::ToUInt8(value, &lowest, &low, &high, &highest);
            return Convert::ToUInt32(highest, high, low, lowest);
        }
	}
}
