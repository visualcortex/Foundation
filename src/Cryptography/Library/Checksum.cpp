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

#include <Dream/Foundation/Cryptography/Checksum.hpp>
#include <Dream/Foundation/Cryptography/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Cryptography.Checksum"

namespace Dream
{
	namespace Cryptography
	{
		size_t Checksum::ComputeHash
			(__in const byte *data,
			 __in size_t sizeData,
			 __out byte hash[SIZE_HASH])
		{
			Checksum checksum;
			checksum.updateHashData(data, sizeData);
			return checksum.getHashValue(hash);
		}

		size_t Checksum::ComputeHash
			(__in IStream &stream,
			 __out byte hash[SIZE_HASH])
		{
			Checksum checksum;
			for (int i = stream.readByte(); i != -1; i = stream.readByte())
			{
				byte x = static_cast<byte>(i);
				checksum.updateHashData(&x, 1);
			}
			
			return checksum.getHashValue(hash);
		}

		int Checksum::CompareHashes
			(__in const byte hash1[SIZE_HASH],
			 __in const byte hash2[SIZE_HASH])
		{
			return memcmp(hash1, hash2, SIZE_HASH);
		}

		Checksum::Checksum()
		{
			resetHashData();
		}

		size_t Checksum::getHashSize() const throw()
		{
			return SIZE_HASH;
		}

		size_t Checksum::getDataSize() const throw()
		{
			return m_sizeData;
		}

		ByteArray Checksum::getHashValue()
		{
			byte hash[SIZE_HASH];
			getHashValue(hash);
			return ByteArray(hash, hash + SIZE_HASH);
		}

		void Checksum::resetHashData()
		{
			m_buffer = 0;
			m_tail = -1;
			m_sizeData = 0;
			m_isComputed = false;
		}

		void Checksum::updateHashData
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

			if (m_tail != -1 && sizeData > 0)
			{
				byte tail[2] = { 
					static_cast<byte>(m_tail),  
					data[0]
				};

				m_buffer += *reinterpret_cast<uint16*>(tail);
				if (m_buffer > 0xFFFF)
				{
					m_buffer += 1;
					m_buffer &= 0xFFFF;
				}

				m_tail = -1;
				data++;
				sizeData--;
				m_sizeData++;
			}

			const uint16 *p = reinterpret_cast<const uint16*>(data);
			for (size_t i = 0; i < sizeData/2; i++)
			{
				m_buffer += *p++;
				if (m_buffer > 0xFFFF)
				{
					m_buffer += 1;
					m_buffer &= 0xFFFF;
				}
			}

			if (sizeData % 2 != 0)
				m_tail = data[sizeData - 1];

			m_sizeData += sizeData;
		}

		size_t Checksum::getHashValue(__out byte hash[SIZE_HASH])
		{
			if (!m_isComputed)
			{
				if (m_tail != -1)
				{
					m_buffer += m_tail;
					if (m_buffer > 0xFFFF)
					{
						m_buffer += 1;
						m_buffer &= 0xFFFF;
					}
				}

				m_buffer += m_sizeData;
				m_isComputed = true;
			}

			uint8 lowest, low, high, highest;
			Convert::ToUInt8(m_buffer, &lowest, &low, &high, &highest);

			hash[0] = highest;
			hash[1] = high;
			hash[2] = low;
			hash[3] = lowest;

			return m_sizeData;
		}
	}
}
