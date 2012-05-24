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

#include <Foundation/Essential/Convert.hpp>

namespace Dream
{
	namespace
	{
		/// TODO: Throw exception if match not found
		byte ucvmap(char w)
		{
			switch (w)
			{
				case '0': return 0;
				case '1': return 1;
				case '2': return 2;
				case '3': return 3;
				case '4': return 4;
				case '5': return 5;
				case '6': return 6;
				case '7': return 7;
				case '8': return 8;
				case '9': return 9;
                case 'A': case 'a': return 10;
				case 'B': case 'b': return 11;
				case 'C': case 'c': return 12;
				case 'D': case 'd': return 13;
				case 'E': case 'e': return 14;
				case 'F': case 'f': return 15;
			}
		
			return 0;
		}
	}

	namespace Convert
	{
        void ToUInt8
			(__in uint32 value,
             __out uint8 *lowest,
             __out uint8 *low,
             __out uint8 *high,
             __out uint8 *highest) throw()
        {
            *lowest  = static_cast<uint8>(value);
            *low     = static_cast<uint8>(value >> 8);
			*high    = static_cast<uint8>(value >> 16);
            *highest = static_cast<uint8>(value >> 24);
        }

		int16 ToInt16
			(__in byte low,
			 __in byte high) throw()
		{
			return static_cast<int16>(low)
				| (static_cast<int16>(high) <<  8);
		}

		uint16 ToUInt16
			(__in byte low, 
			 __in byte high) throw()
		{
			return static_cast<uint16>(low)
				| (static_cast<uint16>(high) <<  8);
		}

        void ToUInt16
			(__in uint32 value,
             __out uint16 *low,
             __out uint16 *high) throw()
		{
            *low  = static_cast<uint16>(value);
			*high = static_cast<uint16>(value >> 16);
		}

		int32 ToInt32
			(__in byte lowest,
			 __in byte low, 
			 __in byte high,
			 __in byte highest) throw()
		{
			return static_cast<int32>(lowest) 
				| (static_cast<int32>(low)     <<  8)
				| (static_cast<int32>(high)    << 16)
				| (static_cast<int32>(highest) << 24);
		}

		uint32 ToUInt32
			(__in byte lowest,
			 __in byte low, 
			 __in byte high, 
			 __in byte highest) throw()
		{
			return static_cast<uint32>(lowest) 
				| (static_cast<uint32>(low)     <<  8)
				| (static_cast<uint32>(high)    << 16)
				| (static_cast<uint32>(highest) << 24);
		}

		void ToUInt32
			(__in uint64 value,
			 __out uint32 *low,
			 __out uint32 *high)
		{
			*low  = static_cast<uint32>(value);
			*high = static_cast<uint32>(value >> 32);
		}

		uint64 ToUInt64(__in uint32 low, __in uint32 high) throw()
		{
			return static_cast<uint64>(low)
				| (static_cast<uint64>(high) << 32);
		}

		string ToHexString(__in const byte *blob, __in size_t sizeBlob)
		{
			static const char cvmap[] = "0123456789ABCDEF";

			string s(sizeBlob*2, 0);
			for (size_t i = 0; i < sizeBlob; i++)
			{
				s[i*2] = cvmap[(blob[i] >> 4) & 0x0f];
				s[i*2 + 1] = cvmap[blob[i] & 0x0F];
			}

			return s;
		}
	
		/// TODO: Throw exception if length of value is not "%2 == 0"
		ByteArray ToByteArray(__in const string &value)
		{
			ByteArray retval;
			for (size_t i = 0; i < value.size()/2; i++)
			{
				byte b = static_cast<byte>
					((ucvmap(value[i*2]) << 4) | ucvmap(value[i*2 + 1]));
				retval.push_back(b);
			}

			return retval;
		}

        string ToString
            (__in const char *src,
             __in size_t sizeSource)
        {
            wchar_t dst[9];
                
            size_t numChars = 0;
            for (numChars = 0; numChars < sizeSource; numChars++)
            {
                const char *tail = src + numChars;
                if (*tail != 0)
                {
                    if (mbtowc(dst + numChars, tail, 1) == -1)
                        dst[numChars] = L'?';
                }
                else
                {
                    dst[numChars] = 0;
                    break;
                }
            }

            return string(dst, dst + numChars);
        }
	}
}
