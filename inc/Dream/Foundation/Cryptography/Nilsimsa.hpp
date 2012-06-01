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

#pragma once

#include <Dream/Foundation/Cryptography/HashAlgorithm.hpp>

namespace Dream
{
	namespace Cryptography
	{
		/** Implementation of the distance based hash algorithm Nilsimsa
		 *
		 *  Inspired by the original C nilsimsa implementation by cmeclax
		 *  http://ixazon.dynip.com/~cmeclax/nilsimsa.html
		 */
		class Nilsimsa : public IHashAlgorithm, Noncopyable
		{
			public:
				/// The size of hash in bytes
				static const size_t SIZE_HASH = 32;
		
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
				 *	\return The value in range [0, 256], where 
				 *            0 - hash1 equal to hash2
				 *          256 - hash1 totally defferent form hash2
				 */
				static int CompareHashes
					(__in const byte x[SIZE_HASH],
					 __in const byte y[SIZE_HASH]);

			public:
				// Constructor
				Nilsimsa();
				virtual ~Nilsimsa() throw(){}

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
				size_t m_sizeData;
				bool   m_isComputed;
				byte   m_abcd[4];
				size_t m_buffer[256];
				byte   m_hash[SIZE_HASH];
		};
	}
}
