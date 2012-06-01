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

#include "Common.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(CryptographyTestSuite)

BOOST_AUTO_TEST_CASE(SHA1TestZero)
{
    SHA1 sha1;
    
    byte rawHash[SHA1::SIZE_HASH];
    size_t sizeData = sha1.getHashValue(rawHash);

    string hash = Convert::ToHexString(rawHash, SHA1::SIZE_HASH);

    BOOST_CHECK(sizeData == 0);
    BOOST_CHECK(_stricmp(hash.c_str(), SHA1_00.c_str()) == 0);
}

BOOST_AUTO_TEST_CASE(SHA1TestStatic)
{
    byte hash1[SHA1::SIZE_HASH] = { 0 };

	BOOST_CHECK_EQUAL(SHA1::ComputeHash(DATA_PART, SIZE_DATA_PART, hash1), SIZE_DATA_PART);
    
    byte hash2[SHA1::SIZE_HASH] = { 0 };
    ByteArray ba = Convert::ToByteArray(SHA1_01);
    memcpy(hash2, &ba[0], SHA1::SIZE_HASH);

    string hash3 = Convert::ToHexString(hash1, SHA1::SIZE_HASH);
    
    BOOST_CHECK(SHA1::CompareHashes(hash1, hash2) == 0);
    BOOST_CHECK(_stricmp(hash3.c_str(), SHA1_01.c_str()) == 0);
}

BOOST_AUTO_TEST_SUITE_END()
