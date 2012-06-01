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

/*
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** License to copy and use this software is granted provided that   **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message     **
 ** Digest Algorithm" in all material mentioning or referencing this **
 ** software or this function.                                       **
 **                                                                  **
 ** License is also granted to make and use derivative works         **
 ** provided that such works are identified as "derived from the RSA **
 ** Data Security, Inc. MD5 Message Digest Algorithm" in all         **
 ** material mentioning or referencing the derived work.             **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */

#include "Precompiled.hpp"

#include <Dream/Foundation/Cryptography/MD5.hpp>
#include <Dream/Foundation/Cryptography/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Cryptography.MD5"

namespace Dream
{
	namespace Cryptography
	{
		namespace
		{
			/** Transformation Constants
			 */
			const byte PADDING[64] =
			{
				0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			/** Basic MD5 functions.
			 */
			uint32 ROTATE_LEFT(__in uint32 x, __in uint32 n)
			{
				return (x << n) | (x >> (32 - n));
			}

			uint32 F(__in uint32 x, __in uint32 y, __in uint32 z)
			{
				return (x & y) | (~x & z);
			}

			uint32 G(__in uint32 x, __in uint32 y, __in uint32 z)
			{
				return (x & z) | (y & ~z);
			}

			uint32 H(__in uint32 x, __in uint32 y, __in uint32 z)
			{
				return x ^ y ^ z;
			}

			uint32 I(__in uint32 x, __in uint32 y, __in uint32 z)
			{
				return y ^ (x | ~z);
			}

			void FF(__inout uint32 &a, __in uint32 b, __in uint32 c,
					__in uint32 d, __in uint32 x, __in uint32 s, __in uint32 ac)
			{
				a = ROTATE_LEFT(a + F(b, c ,d) + x + ac, s) + b;
			}

			void GG(__inout uint32 &a, __in uint32 b, __in uint32 c,
					__in uint32 d, __in uint32 x, __in uint32 s, __in uint32 ac)
			{
				a = ROTATE_LEFT(a + G(b, c ,d) + x + ac, s) + b;
			}

			void HH(__inout uint32 &a, __in uint32 b, __in uint32 c,
					__in uint32 d, __in uint32 x, __in uint32 s, __in uint32 ac)
			{
				a = ROTATE_LEFT(a + H(b, c ,d) + x + ac, s) + b;
			}

			void II(__inout uint32 &a, __in uint32 b, __in uint32 c,
					__in uint32 d, __in uint32 x, __in uint32 s, __in uint32 ac)
			{
				a = ROTATE_LEFT(a + I(b, c ,d) + x + ac, s) + b;
			}

			/** Complex MD5 functions
			 */

			void Encode(__out byte *dest, __in const uint32 *src, __in size_t count)
			{
				preconditions
				{
					DREAM_ASSERT(count % 4 == 0 && "Argument 'count' should be a multiple of 4");
				}

				for (size_t i = 0, j = 0; j < count; i++, j += 4)
				{
					dest[j] =  src[i] & 0xff;
					dest[j + 1] = (src[i] >> 8)  & 0xff;
					dest[j + 2] = (src[i] >> 16) & 0xff;
					dest[j + 3] = (src[i] >> 24) & 0xff;
				}
			}

			void Decode (__out uint32 *dest, __in const byte *src, __in size_t count)
			{
				preconditions
				{
					DREAM_ASSERT(count % 4 == 0 && "Argument 'count' should be a multiple of 4");
				}

				for (size_t i = 0, j = 0; j < count; i++, j += 4)
				{
					dest[i] = ((uint32)src[j]) | (((uint32)src[j + 1]) << 8) | 
								(((uint32)src[j + 2]) << 16) | (((uint32)src[j + 3]) << 24);
				}
			}

			void TransformRound1(__inout uint32 &a, __inout uint32 &b, 
					__inout uint32 &c, __inout uint32 &d, __in const uint32 x[16])
			{
				const uint32 S11 = 7;
				const uint32 S12 = 12;
				const uint32 S13 = 17;
				const uint32 S14 = 22;

				FF(a, b, c, d, x[ 0], S11, 0xd76aa478); // 1
				FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); // 2
				FF(c, d, a, b, x[ 2], S13, 0x242070db); // 3
				FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); // 4
				FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); // 5
				FF(d, a, b, c, x[ 5], S12, 0x4787c62a); // 6
				FF(c, d, a, b, x[ 6], S13, 0xa8304613); // 7
				FF(b, c, d, a, x[ 7], S14, 0xfd469501); // 8
				FF(a, b, c, d, x[ 8], S11, 0x698098d8); // 9
				FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); // 10
				FF(c, d, a, b, x[10], S13, 0xffff5bb1); // 11
				FF(b, c, d, a, x[11], S14, 0x895cd7be); // 12
				FF(a, b, c, d, x[12], S11, 0x6b901122); // 13
				FF(d, a, b, c, x[13], S12, 0xfd987193); // 14
				FF(c, d, a, b, x[14], S13, 0xa679438e); // 15
				FF(b, c, d, a, x[15], S14, 0x49b40821); // 16
			}

			void TransformRound2(__inout uint32 &a, __inout uint32 &b,
					__inout uint32 &c, __inout uint32 &d, __in const uint32 x[16])
			{
				const uint32 S21 = 5;
				const uint32 S22 = 9;
				const uint32 S23 = 14;
				const uint32 S24 = 20;

				GG(a, b, c, d, x[ 1], S21, 0xf61e2562); // 17
				GG(d, a, b, c, x[ 6], S22, 0xc040b340); // 18
				GG(c, d, a, b, x[11], S23, 0x265e5a51); // 19
				GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); // 20
				GG(a, b, c, d, x[ 5], S21, 0xd62f105d); // 21
				GG(d, a, b, c, x[10], S22,  0x2441453); // 22
				GG(c, d, a, b, x[15], S23, 0xd8a1e681); // 23
				GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); // 24
				GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); // 25
				GG(d, a, b, c, x[14], S22, 0xc33707d6); // 26
				GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); // 27
				GG(b, c, d, a, x[ 8], S24, 0x455a14ed); // 28
				GG(a, b, c, d, x[13], S21, 0xa9e3e905); // 29
				GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); // 30
				GG(c, d, a, b, x[ 7], S23, 0x676f02d9); // 31
				GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); // 32
			}

			void TransformRound3(__inout uint32 &a, __inout uint32 &b,
					__inout uint32 &c, __inout uint32 &d, __in const uint32 x[16])
			{
				const uint32 S31 = 4;
				const uint32 S32 = 11;
				const uint32 S33 = 16;
				const uint32 S34 = 23;

				HH(a, b, c, d, x[ 5], S31, 0xfffa3942); // 33
				HH(d, a, b, c, x[ 8], S32, 0x8771f681); // 34
				HH(c, d, a, b, x[11], S33, 0x6d9d6122); // 35
				HH(b, c, d, a, x[14], S34, 0xfde5380c); // 36
				HH(a, b, c, d, x[ 1], S31, 0xa4beea44); // 37
				HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); // 38
				HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); // 39
				HH(b, c, d, a, x[10], S34, 0xbebfbc70); // 40
				HH(a, b, c, d, x[13], S31, 0x289b7ec6); // 41
				HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); // 42
				HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); // 43
				HH(b, c, d, a, x[ 6], S34,  0x4881d05); // 44
				HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); // 45
				HH(d, a, b, c, x[12], S32, 0xe6db99e5); // 46
				HH(c, d, a, b, x[15], S33, 0x1fa27cf8); // 47
				HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); // 48
			}

			void TransformRound4(__inout uint32 &a, __inout uint32 &b,
					__inout uint32 &c, __inout uint32 &d, __in const uint32 x[16])
			{
				const uint32 S41 = 6;
				const uint32 S42 = 10;
				const uint32 S43 = 15;
				const uint32 S44 = 21;

				II(a, b, c, d, x[ 0], S41, 0xf4292244); // 49
				II(d, a, b, c, x[ 7], S42, 0x432aff97); // 50
				II(c, d, a, b, x[14], S43, 0xab9423a7); // 51
				II(b, c, d, a, x[ 5], S44, 0xfc93a039); // 52
				II(a, b, c, d, x[12], S41, 0x655b59c3); // 53
				II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); // 54
				II(c, d, a, b, x[10], S43, 0xffeff47d); // 55
				II(b, c, d, a, x[ 1], S44, 0x85845dd1); // 56
				II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); // 57
				II(d, a, b, c, x[15], S42, 0xfe2ce6e0); // 58
				II(c, d, a, b, x[ 6], S43, 0xa3014314); // 59
				II(b, c, d, a, x[13], S44, 0x4e0811a1); // 60
				II(a, b, c, d, x[ 4], S41, 0xf7537e82); // 61
				II(d, a, b, c, x[11], S42, 0xbd3af235); // 62
				II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); // 63
				II(b, c, d, a, x[ 9], S44, 0xeb86d391); // 64
			}

			/** MD5 basic transformation: transforms state based on block
			 */
			void Transform(__inout uint32 state[4], __in const byte block[64])
			{
				uint32 a = state[0];
				uint32 b = state[1];
				uint32 c = state[2];
				uint32 d = state[3];

				uint32 x[16];
				Decode(x, block, 64);

				TransformRound1(a, b, c, d, x);
				TransformRound2(a, b, c, d, x);
				TransformRound3(a, b, c, d, x);
				TransformRound4(a, b, c, d, x);

				state[0] += a;
				state[1] += b;
				state[2] += c;
				state[3] += d;
			}

			//-------------------------------------------------------------------------
			void Update(const byte *stream, size_t sizeStream,
					__inout uint32 state[4], __inout size_t count[2],  
						__inout byte buffer[64]) throw()
			{
				preconditions
				{
					DREAM_ASSERT(stream != nullptr);
				}

				// Compute number of bytes mod 64
	  			size_t index = (count[0] >> 3) & 0x3F;

				// Update number of bits
				count[0] += sizeStream << 3;
	  			if (count[0] < (sizeStream << 3))
					count[1]++;
	  			count[1] += sizeStream >> 29;

		  		// Transform as many times as possible
		  		size_t i = 0;
				
				size_t sizeTransferBlock = 64 - index;
				if (sizeStream >= sizeTransferBlock)
	  			{
		 			memcpy(buffer + index, stream, sizeTransferBlock);
			 		Transform(state, buffer);

		 			for (i = sizeTransferBlock; i + 63 < sizeStream; i += 64)
		   				Transform(state, stream + i);

		 			index = 0;
		  		}

		  		// Buffer remaining input
	  			memcpy(buffer + index, stream + i, sizeStream - i);
			}
		}

		size_t MD5::ComputeHash
			(__in const byte *data, 
			 __in size_t sizeData, 
			 __out byte hash[SIZE_HASH])
		{
			MD5 md5;
			md5.updateHashData(data, sizeData);
			return md5.getHashValue(hash);
		}

		size_t MD5::ComputeHash
			(__in IStream &stream,
			 __out byte hash[SIZE_HASH])
		{
			MD5 md5;
			for (int i = stream.readByte(); i != -1; i = stream.readByte())
			{
				byte x = static_cast<byte>(i);
				md5.updateHashData(&x, 1);
			}

			return md5.getHashValue(hash);
		}

		int MD5::CompareHashes
			(__in const byte hash1[SIZE_HASH],
			 __in const byte hash2[SIZE_HASH])
		{
			return memcmp(hash1, hash2, SIZE_HASH);
		}

		MD5::MD5()
		{
			resetHashData();
		}

		size_t MD5::getHashSize() const throw()
		{
			return SIZE_HASH;
		}

		size_t MD5::getDataSize() const throw()
		{
			return m_sizeData;
		}

		ByteArray MD5::getHashValue()
		{
			byte hash[SIZE_HASH];
			getHashValue(hash);
			return ByteArray(hash, hash + SIZE_HASH);
		}

		void MD5::resetHashData()
		{
			m_state[0] = 0x67452301;
			m_state[1] = 0xefcdab89;
			m_state[2] = 0x98badcfe;
			m_state[3] = 0x10325476;
        
			m_count[0] = 0;
			m_count[1] = 0;
			
			memset(m_buffer, 0, 64);

			m_sizeData = 0;
			m_isComputed = false;
		}

		void MD5::updateHashData
			(__in const byte *data,
			 __in size_t sizeData)
		{
			preconditions
			{
				if (m_isComputed)
					throw Exception(SOURCE_CLASS, DREAM_E_HASH_ALREADY_COMPUTED);

				if (data == nullptr && sizeData != 0)
					throw Exception(SOURCE_CLASS, DREAM_E_INVALID_ARGUMENTS);
			}

			Update(data, sizeData, m_state, m_count, m_buffer);
			m_sizeData += sizeData;
		}

		size_t MD5::getHashValue(__out byte hash[SIZE_HASH])
		{
			if (!m_isComputed)
			{
				byte bits[8];
				Encode(bits, m_count, 8);

				size_t index = (m_count[0] >> 3) & 0x3f;
				size_t sizePadding = (index < 56) ? (56 - index) : (120 - index);
	
				Update(PADDING, sizePadding, m_state, m_count, m_buffer);

				// Append length (before padding)
				Update(bits, 8, m_state, m_count, m_buffer);

				m_isComputed = true;
			}

			Encode(hash, m_state, 16);
			return m_sizeData;
		}
	}
}
