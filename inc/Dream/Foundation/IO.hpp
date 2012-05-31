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

#include <Dream/Foundation/IO/Directory.hpp>
#include <Dream/Foundation/IO/Exception.hpp>
#include <Dream/Foundation/IO/File.hpp>
#include <Dream/Foundation/IO/FileAccessRights.hpp>
#include <Dream/Foundation/IO/FileFeatures.hpp>
#include <Dream/Foundation/IO/FileMap.hpp>
#include <Dream/Foundation/IO/FileMapAccessRights.hpp>
#include <Dream/Foundation/IO/FileOpenMode.hpp>
#include <Dream/Foundation/IO/FileSeekMode.hpp>
#include <Dream/Foundation/IO/FileShareMode.hpp>
#include <Dream/Foundation/IO/FileStream.hpp>
#include <Dream/Foundation/IO/FileView.hpp>
#include <Dream/Foundation/IO/FileViewAccessRights.hpp>
#include <Dream/Foundation/IO/Redirection.hpp>
#include <Dream/Foundation/IO/Scan.hpp>
#include <Dream/Foundation/IO/ScanListener.hpp>

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	pragma comment(lib, DREAM_COMPOSE_LIBRARY_NAME("Dream.Foundation.IO"))
#endif
