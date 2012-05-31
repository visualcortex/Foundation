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
	namespace System
	{
		class Environment
		{
			public:
				/// Retrieves the NetBIOS name of the local computer
				static string GetMachineName();

				/// Retrieves the calling thread's last-error code value
				static result_t GetLastError() throw();

				/// Retrieves a string array of the currently available disk drives
				static StringArray GetLogicalDrives();

				/// Retrieves the version number of the current operating system
				static string GetOSVersion();
		};
	}
}
