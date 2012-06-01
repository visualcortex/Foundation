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

BOOST_AUTO_TEST_CASE(ChecksumTestZero)
{
    Checksum checksum;
    
    byte rawHash[Checksum::SIZE_HASH];
    size_t sizeData = checksum.getHashValue(rawHash);

    string hash = Convert::ToHexString(rawHash, Checksum::SIZE_HASH);

    BOOST_CHECK(sizeData == 0);
    BOOST_CHECK(_stricmp(hash.c_str(), CHECKSUM_00.c_str()) == 0);
}

BOOST_AUTO_TEST_CASE(ChecksumTestStatic)
{
    std::auto_ptr<byte> safebuf(new byte[SIZE_DATA]);
    byte *data = safebuf.get();

    for (size_t i = 0; i < NUM_DATA_PARTS; i++)
        memcpy(data + i*SIZE_DATA_PART, DATA_PART, SIZE_DATA_PART);

    uint32 checksum = 0;
    byte buffer[Checksum::SIZE_HASH] = { 0 };

	BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, SIZE_DATA, buffer), SIZE_DATA);    
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_01);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, SIZE_DATA - 1, buffer), SIZE_DATA - 1);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_02);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, SIZE_DATA - 2, buffer), SIZE_DATA - 2);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_03);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, SIZE_DATA - 3, buffer), SIZE_DATA - 3);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_04);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, 3, buffer), 3);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_05);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, 2, buffer), 2);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_06);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, 1, buffer), 1);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_07);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, 0, buffer), 0);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_08);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, SIZE_DATA/2, buffer), SIZE_DATA/2);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_09);

    BOOST_CHECK_EQUAL(Checksum::ComputeHash(data, SIZE_DATA/2 + 1, buffer), SIZE_DATA/2 + 1);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);    
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_10);
}

BOOST_AUTO_TEST_CASE(ChecksumTestDynamic)
{
    std::auto_ptr<byte> safebuf(new byte[SIZE_DATA]);
    byte *data = safebuf.get();

    for (size_t i = 0; i < NUM_DATA_PARTS; i++)
        memcpy(data + i*SIZE_DATA_PART, DATA_PART, SIZE_DATA_PART);

    uint32 checksum = 0;
    byte buffer[Checksum::SIZE_HASH] = { 0 };

    Checksum gen;
    gen.updateHashData(data, SIZE_DATA/2);
    gen.updateHashData(data + SIZE_DATA/2, SIZE_DATA - SIZE_DATA/2);

	BOOST_CHECK_EQUAL(gen.getHashValue(buffer), SIZE_DATA);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_01);

    gen.resetHashData();

    gen.updateHashData(data, (SIZE_DATA - 1)/2);
    gen.updateHashData(data + (SIZE_DATA - 1)/2, (SIZE_DATA - 1) - (SIZE_DATA - 1)/2);

	BOOST_CHECK_EQUAL(gen.getHashValue(buffer), SIZE_DATA - 1);
    checksum = Convert::ToUInt32(buffer[3], buffer[2], buffer[1], buffer[0]);
    BOOST_CHECK_EQUAL(checksum, CHECKSUM_02);
}

BOOST_AUTO_TEST_SUITE_END()
