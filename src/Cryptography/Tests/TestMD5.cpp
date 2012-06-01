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

BOOST_AUTO_TEST_CASE(MD5TestZero)
{
    MD5 md5;
    
    byte rawHash[MD5::SIZE_HASH];
    size_t sizeData = md5.getHashValue(rawHash);

    string hash = Convert::ToHexString(rawHash, MD5::SIZE_HASH);

    BOOST_CHECK(sizeData == 0);
    BOOST_CHECK(_stricmp(hash.c_str(), MD5_00.c_str()) == 0);
}

BOOST_AUTO_TEST_CASE(MD5TestStatic)
{
    byte hash1[MD5::SIZE_HASH] = { 0 };

	BOOST_CHECK_EQUAL(MD5::ComputeHash(DATA_PART, SIZE_DATA_PART, hash1), SIZE_DATA_PART);
    
    byte hash2[MD5::SIZE_HASH] = { 0 };
    ByteArray ba = Convert::ToByteArray(MD5_01);
    memcpy(hash2, &ba[0], MD5::SIZE_HASH);

    string hash3 = Convert::ToHexString(hash1, MD5::SIZE_HASH);
    
    BOOST_CHECK(MD5::CompareHashes(hash1, hash2) == 0);
    BOOST_CHECK(_stricmp(hash3.c_str(), MD5_01.c_str()) == 0);
}

BOOST_AUTO_TEST_SUITE_END()
