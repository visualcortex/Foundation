/******************************************************************************
 * @file
 * @author Ivan Makarov <im.visualcortex@gmail.com>
 * 
 * @section LICENSE
 *
 * Copyright (C) 2012, Ivan Makarov
 * Licensed under the GNU GPL license (version 2 or any later).
 *
 *****************************************************************************/

#include "Precompiled.hpp"

#include <Dream/Foundation/Cryptography/Nilsimsa.hpp>
#include <Dream/Foundation/Cryptography/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Cryptography.Nilsimsa"

namespace Dream
{
	namespace Cryptography
	{
		namespace
		{
			/** Nilsimsa's standard hash function 
			 * \note The code used to calculate the transformation table:
			 *		int j = 0;
			 *		for (int i = 0; i < 256; i++) {
			 *			j = ((j*53 + 1) & 255) << 1;
			 *			if (j > 255)
			 *				j -= 255;
			 *
			 *			for (int k = 0; k < i; k++) {
			 *				if (j == tran[k]) {
			 *					j = (j + 1) & 255;
			 *					k = 0;
			 *				}
			 *
			 *				tran[i] = j;
			 *			}
			 *		}
			 */	
			byte nshash(__in byte a, __in byte b, __in byte c, __in int n)
			{
				static const byte s[256] =
				{
					0x00, 0xd6, 0x9e, 0x6f, 0xf9, 0x1d, 0x04, 0xab, 0xd0, 0x22,
					0x16, 0x1f, 0xd8, 0x73, 0xa1, 0xac, 0x3b, 0x70, 0x62, 0x96,
					0x1e, 0x6e, 0x8f, 0x39, 0x9d, 0x05, 0x14, 0x4a, 0xa6, 0xbe,
					0xae, 0x0e, 0xcf, 0xb9, 0x9c, 0x9a, 0xc7, 0x68, 0x13, 0xe1,
					0x2d, 0xa4, 0xeb, 0x51, 0x8d, 0x64, 0x6b, 0x50, 0x23, 0x80,
					0x03, 0x41, 0xec, 0xbb, 0x71, 0xcc, 0x7a, 0x86, 0x7f, 0x98,
					0xf2, 0x36, 0x5e, 0xee, 0x8e, 0xce, 0x4f, 0xb8, 0x32, 0xb6,
					0x5f, 0x59, 0xdc, 0x1b, 0x31, 0x4c, 0x7b, 0xf0, 0x63, 0x01,
					0x6c, 0xba, 0x07, 0xe8, 0x12, 0x77, 0x49, 0x3c, 0xda, 0x46,
					0xfe, 0x2f, 0x79, 0x1c, 0x9b, 0x30, 0xe3, 0x02, 0xd6, 0x9e,
					0x72, 0x37, 0xc8, 0xd2, 0xf6, 0xdf, 0x58, 0x74, 0x0a, 0x26,
					0xbf, 0x19, 0x5c, 0x1a, 0xc6, 0xff, 0x99, 0x5d, 0x84, 0xaa,
					0x66, 0x3e, 0xaf, 0x78, 0xb3, 0x20, 0x43, 0xc1, 0xed, 0x24,
					0xea, 0xe6, 0x3f, 0x18, 0xf3, 0xa0, 0x42, 0x57, 0x08, 0x53,
					0x60, 0xc3, 0xc0, 0x83, 0x40, 0x82, 0xd7, 0x09, 0xbd, 0x44,
					0x2a, 0x67, 0xa8, 0x93, 0xe0, 0xc2, 0x56, 0x9f, 0xd9, 0xdd,
					0x85, 0x15, 0xb4, 0x8a, 0x27, 0x28, 0x92, 0x76, 0xde, 0xef,
					0xf8, 0xb2, 0xb7, 0xc9, 0x3d, 0x45, 0x94, 0x4b, 0x11, 0x0d,
					0x65, 0xd5, 0x34, 0x8b, 0x91, 0x0c, 0xfa, 0x87, 0xe9, 0x7c,
					0x5b, 0xb1, 0x4d, 0xe5, 0xd4, 0xcb, 0x10, 0xa2, 0x17, 0x89,
					0xbc, 0xdb, 0xb0, 0xe2, 0x97, 0x88, 0x52, 0xf7, 0x48, 0xd3,
					0x61, 0x2c, 0x3a, 0x06, 0x7e, 0x2e, 0x0f, 0x38, 0x33, 0x21,
					0xad, 0xa5, 0x54, 0xca, 0xa7, 0x29, 0xfc, 0x5a, 0x47, 0x69,
					0x7d, 0xc5, 0x95, 0xb5, 0xf4, 0x0b, 0x90, 0xa3, 0x81, 0x6d,
					0x25, 0x55, 0x35, 0xf5, 0x75, 0x80, 0x2b, 0xd1, 0x8c, 0xfb,
					0xf1, 0xcd, 0xe4, 0x6a, 0xe7, 0xa9
				};

				return ((s[(a + n) & 255]^s[b]*(2*n + 1)) + s[c^s[n]]) & 255;
			}
		}

		size_t Nilsimsa::ComputeHash
			(__in const byte *data, 
			 __in size_t sizeData, 
			 __out byte hash[SIZE_HASH])
		{
			Nilsimsa nilsimsa;
			nilsimsa.updateHashData(data, sizeData);
			return nilsimsa.getHashValue(hash);
		}

		size_t Nilsimsa::ComputeHash(__in IStream &stream, __out byte hash[SIZE_HASH])
		{
			Nilsimsa nilsimsa;
			for (int i = stream.readByte(); i != -1; i = stream.readByte())
			{
				byte x = static_cast<byte>(i);
				nilsimsa.updateHashData(&x, 1);
			}

			return nilsimsa.getHashValue(hash);
		}

		int Nilsimsa::CompareHashes
			(__in const byte x[SIZE_HASH],
			 __in const byte y[SIZE_HASH])
		{
			int distance = 0;
			for (size_t i = 0; i < SIZE_HASH; i++)
			{
				byte z = x[i] ^ y[i];
				for (size_t j = 0; j < 8; j++, z >>= 1)
					if (z & 1)
						distance++;
			}

			return distance;
		}

		Nilsimsa::Nilsimsa()
		{
			resetHashData();
		}

		size_t Nilsimsa::getHashSize() const throw()
		{
			return SIZE_HASH;
		}

		size_t Nilsimsa::getDataSize() const throw()
		{
			return m_sizeData;
		}

		ByteArray Nilsimsa::getHashValue()
		{
			byte hash[SIZE_HASH];
			getHashValue(hash);
			return ByteArray(hash, hash + SIZE_HASH);
		}

		void Nilsimsa::resetHashData()
		{
			m_sizeData = 0;
			m_isComputed = false;
        
			memset(m_buffer, 0, 256*sizeof(size_t));
			memset(m_hash, 0, SIZE_HASH);
		}

		void Nilsimsa::updateHashData
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

			if (m_sizeData < 4)
			{
				for (size_t i = std::min(sizeData, 4 - m_sizeData); i > 0; i--)
				{
					m_abcd[m_sizeData++] = *data++;
					sizeData--;
				}

				if (m_sizeData == 4)
				{
					byte a = m_abcd[0];
					byte b = m_abcd[1];
					byte c = m_abcd[2];
					byte d = m_abcd[3];

					m_buffer[nshash(c, b, a, 0)]++; // 1'st three

					m_buffer[nshash(d, c, b, 0)]++; // 1'st four
					m_buffer[nshash(d, c, a, 1)]++;
					m_buffer[nshash(d, b, a, 2)]++;
				}
			}

			if (m_sizeData >= 4)
			{
				byte a = m_abcd[0];
				byte b = m_abcd[1];
				byte c = m_abcd[2];
				byte d = m_abcd[3];

				for (size_t i = 0; i < sizeData; i++)
				{
					byte x = data[i];

					m_buffer[nshash(x, d, c, 0)]++;

					m_buffer[nshash(x, d, b, 1)]++;
					m_buffer[nshash(x, c, b, 2)]++;

					m_buffer[nshash(x, d, a, 3)]++;
					m_buffer[nshash(x, c, a, 4)]++;
					m_buffer[nshash(x, b, a, 5)]++;

					m_buffer[nshash(a, d, x, 6)]++;
					m_buffer[nshash(a, b, x, 7)]++;

					m_abcd[0] = b;
					m_abcd[1] = c;
					m_abcd[2] = d;
					m_abcd[3] = x;
				}

				m_sizeData += sizeData;
			}
		}

		size_t Nilsimsa::getHashValue(__out byte hash[SIZE_HASH])
		{
			if (!m_isComputed)
			{
				if (m_sizeData >= 4)
				{
					size_t numTrigrams = 8*m_sizeData - 28;
					// round down because criterion is "> threshold"
					size_t threshold = numTrigrams/256;
		
					for (size_t i = 0; i < 256; i++)
						m_hash[i >> 3] += ((m_buffer[i] > threshold) << (i & 7));
				}
				else
				{
					m_sizeData = 0;
				}

				m_isComputed = true;
			}

			memcpy(hash, m_hash, SIZE_HASH);
			return m_sizeData;
		}
	}
}
