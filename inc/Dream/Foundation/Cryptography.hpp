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

#include <Dream/Foundation/Cryptography/Checksum.hpp>
#include <Dream/Foundation/Cryptography/HashAlgorithm.hpp>
#include <Dream/Foundation/Cryptography/MD5.hpp>
#include <Dream/Foundation/Cryptography/Nilsimsa.hpp>
#include <Dream/Foundation/Cryptography/SHA1.hpp>

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	pragma comment(lib, DREAM_COMPOSE_LIBRARY_NAME("Dream.Foundation.Cryptography"))
#endif
