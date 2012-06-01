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

#include <Dream/Foundation/Essential.hpp>

namespace Dream
{
	namespace Cryptography
	{
		interface IHashAlgorithm : public IAbstract
		{
			/// Returns the size of hash in bytes
			virtual size_t getHashSize() const throw() = 0;

			/// Returns the size of data used
			virtual size_t getDataSize() const throw() = 0;

			/// Returns the computed hash value
			virtual ByteArray getHashValue() = 0;

			/// Resets the hash data
			virtual void resetHashData() = 0;

			/** Updates the hash data
			 *  \param data The data to be appended to the hash value
			 *  \param sizeData The size of data to be appended
			 */
			virtual void updateHashData
				(__in const byte *data,
				 __in size_t sizeData) = 0;
		};
	}
}
