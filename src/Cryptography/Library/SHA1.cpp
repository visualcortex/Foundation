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

#include <Dream/Foundation/Cryptography/SHA1.hpp>
#include <Dream/Foundation/Cryptography/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Cryptography.SHA1"

namespace Dream
{
	namespace Cryptography
	{
		size_t SHA1::ComputeHash
			(__in const byte *data,
			 __in size_t sizeData,
			 __out byte hash[SHA1::SIZE_HASH])
		{
			SHA1 sha1;
			sha1.updateHashData(data, sizeData);
			return sha1.getHashValue(hash);
		}

		size_t SHA1::ComputeHash
			(__in IStream &stream,
			 __out byte hash[SIZE_HASH])
		{
			SHA1 sha1;
			for (int i = stream.readByte(); i != -1; i = stream.readByte())
			{
				byte x = static_cast<byte>(i);
				sha1.updateHashData(&x, 1);
			}

			return sha1.getHashValue(hash);
		}

		int SHA1::CompareHashes
			(__in const byte hash1[SHA1::SIZE_HASH],
			 __in const byte hash2[SHA1::SIZE_HASH])
		{
			return memcmp(hash1, hash2, SIZE_HASH);
		}

		SHA1::SHA1()
		{
			resetHashData();
		}

		size_t SHA1::getHashSize() const throw()
		{
			return SIZE_HASH;
		}

		size_t SHA1::getDataSize() const throw()
		{
			return m_sizeData;
		}

		ByteArray SHA1::getHashValue()
		{
			byte hash[SIZE_HASH];
			getHashValue(hash);
			return ByteArray(hash, hash + SIZE_HASH);
		}

		void SHA1::resetHashData()
		{
			H[0] = 0x67452301;
			H[1] = 0xEFCDAB89;
			H[2] = 0x98BADCFE;
			H[3] = 0x10325476;
			H[4] = 0xC3D2E1F0;

			m_sizeMessageLow = 0;
			m_sizeMessageHigh = 0;
			m_indexMessageBlock = 0;
			m_isComputed = false;
			m_isCorrupted = false;
			m_sizeData = 0;

			memset(m_hash, 0, SIZE_HASH);
		}


		size_t SHA1::getHashValue(__out byte hash[SHA1::SIZE_HASH])
		{
			if (m_isCorrupted)
				throw Exception(SOURCE_CLASS, DREAM_E_INVALID_HASH);

			if (!m_isComputed)
			{
				// Pad the current message block to 512 bits
				if (m_indexMessageBlock > 55)
				{
					m_arrayMessageBlocks[m_indexMessageBlock++] = 0x80;
					while (m_indexMessageBlock < 64)
						m_arrayMessageBlocks[m_indexMessageBlock++] = 0;

					processMessageBlock();

					while (m_indexMessageBlock < 56)
						m_arrayMessageBlocks[m_indexMessageBlock++] = 0;
				}
				else
				{
					m_arrayMessageBlocks[m_indexMessageBlock++] = 0x80;
					while (m_indexMessageBlock < 56)
						m_arrayMessageBlocks[m_indexMessageBlock++] = 0;
				}

				m_arrayMessageBlocks[56] = (m_sizeMessageHigh >> 24) & 0xFF;
				m_arrayMessageBlocks[57] = (m_sizeMessageHigh >> 16) & 0xFF;
				m_arrayMessageBlocks[58] = (m_sizeMessageHigh >>  8) & 0xFF;
				m_arrayMessageBlocks[59] = (m_sizeMessageHigh      ) & 0xFF;

				m_arrayMessageBlocks[60] = (m_sizeMessageLow  >> 24) & 0xFF;
				m_arrayMessageBlocks[61] = (m_sizeMessageLow  >> 16) & 0xFF;
				m_arrayMessageBlocks[62] = (m_sizeMessageLow  >>  8) & 0xFF;
				m_arrayMessageBlocks[63] = (m_sizeMessageLow       ) & 0xFF;

				processMessageBlock();

				for (size_t i = 0; i < 5; i++)
				{
					uint8 lowest, low, high, highest;
					Convert::ToUInt8(H[i], &lowest, &low, &high, &highest);

					m_hash[4*i + 0] = highest;
					m_hash[4*i + 1] = high;
					m_hash[4*i + 2] = low;
					m_hash[4*i + 3] = lowest;
				}

				m_isComputed = true;
			}

			memcpy(hash, m_hash, SIZE_HASH);

			return m_sizeData;
		}

		void SHA1::updateHashData(__in const byte *data, __in size_t sizeData)
		{
			preconditions
			{
				if (m_isComputed)
					throw Exception(SOURCE_CLASS, DREAM_E_HASH_ALREADY_COMPUTED);

				if (m_isCorrupted)
					throw Exception(SOURCE_CLASS, DREAM_E_INVALID_HASH);

				if (data == nullptr && sizeData != 0)
					throw Exception(SOURCE_CLASS, DREAM_E_INVALID_ARGUMENTS);
			}

			for (size_t i = 0; i < sizeData; i++)
			{
				m_arrayMessageBlocks[m_indexMessageBlock++] = (*data & 0xFF);

				m_sizeMessageLow += 8;
				m_sizeMessageLow &= 0xFFFFFFFF;

				if (m_sizeMessageLow == 0)
				{
					m_sizeMessageHigh++;
					m_sizeMessageHigh &= 0xFFFFFFFF;

					// Message is too long
					if (m_sizeMessageHigh == 0)
					{
						m_isCorrupted = true;
						throw Exception(SOURCE_CLASS, DREAM_E_INVALID_HASH);
					}
				}

				if (m_indexMessageBlock == 64)
					processMessageBlock();

				data++;
			}

			m_sizeData += sizeData;
		}
    
		void SHA1::processMessageBlock()
		{
			const uint32 K[] = {
				0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
			};

			uint32 W[80];
			for (int i = 0; i < 16; i++) {
				W[i]  = (uint32)m_arrayMessageBlocks[i * 4 + 0] << 24;
				W[i] |= (uint32)m_arrayMessageBlocks[i * 4 + 1] << 16;
				W[i] |= (uint32)m_arrayMessageBlocks[i * 4 + 2] << 8;
				W[i] |= (uint32)m_arrayMessageBlocks[i * 4 + 3];
			}

			for (int i = 16; i < 80; i++)
				W[i] = Algorithm::CircularShift(1, W[i-3]^W[i-8]^W[i-14]^W[i-16]);

			uint32 A = H[0];
			uint32 B = H[1];
			uint32 C = H[2];
			uint32 D = H[3];
			uint32 E = H[4];

			for (int i = 0; i < 20; i++)
			{
				uint32 T = (Algorithm::CircularShift(5, A) + 
					((B & C) | ((~B) & D)) + E + W[i] + K[0]) & 0xFFFFFFFF;

				E = D;
				D = C;
				C = Algorithm::CircularShift(30, B);
				B = A;
				A = T;
			}

			for (int i = 20; i < 40; i++)
			{
				uint32 T = (Algorithm::CircularShift(5, A) + 
					(B ^ C ^ D) + E + W[i] + K[1]) & 0xFFFFFFFF;

				E = D;
				D = C;
				C = Algorithm::CircularShift(30, B);
				B = A;
				A = T;
			}

			for (int i = 40; i < 60; i++)
			{
				uint32 T = (Algorithm::CircularShift(5, A) +
					((B & C) | (B & D) | (C & D)) + E + W[i] + K[2]) & 0xFFFFFFFF;

				E = D;
				D = C;
				C = Algorithm::CircularShift(30, B);
				B = A;
				A = T;
			}

			for (int i = 60; i < 80; i++)
			{
				uint32 T = (Algorithm::CircularShift(5, A) + 
					(B ^ C ^ D) + E + W[i] + K[3]) & 0xFFFFFFFF;

				E = D;
				D = C;
				C = Algorithm::CircularShift(30, B);
				B = A;
				A = T;
			}

			H[0] = (H[0] + A) & 0xFFFFFFFF;
			H[1] = (H[1] + B) & 0xFFFFFFFF;
			H[2] = (H[2] + C) & 0xFFFFFFFF;
			H[3] = (H[3] + D) & 0xFFFFFFFF;
			H[4] = (H[4] + E) & 0xFFFFFFFF;

			m_indexMessageBlock = 0;
		}
	}
}
