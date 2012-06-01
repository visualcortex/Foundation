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

#include <Dream/Foundation/Cryptography/HashAlgorithm.hpp>

namespace Dream
{
	namespace Cryptography
	{
		class MD5 : public IHashAlgorithm, Noncopyable
		{
			public:
				/// The size of hash in bytes
				static const size_t SIZE_HASH = 16;

				/** Computes the hash value for the specified byte array
				 * \param data The input to compute the hash value for
				 * \param sizeData The number of bytes in the input data
				 * \param hash The computed hash value
				 * \return The size of data used to compute the hash value
				 */
				static size_t ComputeHash
					(__in const byte *data,
					 __in size_t sizeData,
 					 __out byte hash[SIZE_HASH]);

				/** Computes the hash value for the specified stream
				 * \param stream The stream to compute the hash value for
				 * \param hash The computed hash value
				 * \return The size of data used to compute the hash value
				 */
				static size_t ComputeHash
					(__in IStream &stream,
					 __out byte hash[SIZE_HASH]);

				/** Compares hashes
				 *	\param hash1 The first hash to be compared
				 *	\param hash2 The second hash to be compared
				 *	\return -1 - hash1 less than hash2	 
				 *           0 - hash1 equal to hash2
				 *           1 - hash1 greater than hash2
				 */
				static int CompareHashes
					(__in const byte hash1[SIZE_HASH],
					 __in const byte hash2[SIZE_HASH]);

			public:
				/// Constructor
				MD5();
				virtual ~MD5() throw(){}

			public:
				/** Returns the computed hash value
				 *  \param hash The computed hash value
				 *  \return The size of data used
				 */
				size_t getHashValue(__out byte hash[SIZE_HASH]);

			public:
				/// Returns the size of hash in bytes
				virtual size_t getHashSize() const throw() override;

				/// Returns the size of data used
				virtual size_t getDataSize() const throw() override;

				/// Returns the computed hash value
				virtual ByteArray getHashValue() override;

				/// Resets the hash data
				virtual void resetHashData() override;

				/** Updates the hash data
				 *  \param data The data to be appended to the hash value
				 *  \param sizeData The size of data to be appended
				 */
				virtual void updateHashData
					(__in const byte *data,
					 __in size_t sizeData) override;

			private:
				uint32 m_state[4];      // State (ABCD)			
				size_t m_count[2];      // Number of bits, modulo 2^64 (lsb first)			
				byte   m_buffer[64];    // Input cbuffer
				size_t m_sizeData;
				bool   m_isComputed;
		};
	}
}
