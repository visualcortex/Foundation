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

BOOST_AUTO_TEST_CASE(NilsimsaTestZero)
{
    Nilsimsa nilsimsa;
    
    byte rawHash[Nilsimsa::SIZE_HASH];
    size_t sizeData = nilsimsa.getHashValue(rawHash);

    string hash = Convert::ToHexString(rawHash, Nilsimsa::SIZE_HASH);

    BOOST_CHECK(sizeData == 0);
    BOOST_CHECK(_stricmp(hash.c_str(), NILSIMSA_00.c_str()) == 0);
}

BOOST_AUTO_TEST_CASE(NilsimsaTestStatic)
{}

BOOST_AUTO_TEST_SUITE_END()
